# SQLの発行の仕方
お作法各種。

## テーブルの作成とdbinfoへの保存
CREATE TABLE文は、前述と同じ理由により「dbinfo」の中に保存をします。

保存ファイルについてはいくつかありまして、以下のいずれかを採用しております。

* 全部１ファイルにまとめる。小さな案件ならこれでOK。目安としては、テーブル数が20未満くらい
* 意味のあるカテゴリごとにまとめる。大きな案件だとこっちのほうが取り回しやすいです

今回は小さいので、１ファイルで。ファイル名は any.sql ってしておきましょう。    
先頭に、コメント＆「きわめて念のために」SET NAMESを入れる癖が付いております。…そろそろSET NAMEいらないかなぁ、ともおもうのですが。

    -- MagicWeaponManual用
    -- SQL一式
    
    -- まず文字コードを指定
    SET NAMES utf8;
    
    -- レシートテーブル
    DROP TABLE IF EXISTS sales_receipt;
    CREATE TABLE sales_receipt (
      `sales_receipt_id` varbinary(64) NOT NULL COMMENT '一意なレシート用ID',
      `user_id` varbinary(64) NOT NULL COMMENT 'ユーザID',
      `account_title_id` varbinary(64) NOT NULL COMMENT '科目ID',
      `amount` int NOT NULL COMMENT '金額',
      `sales_receipt_date` date NOT NULL COMMENT 'レシート日付',
      PRIMARY KEY (`sales_receipt_id`)
    )CHARACTER SET 'utf8', ENGINE=InnoDB, COMMENT='１レコードが１レシートなテーブル';

ポイントは「レコード毎のコメント＆テーブルのコメントをちゃんとかく」。プログラム的にはなくても動きますが、色々が諸々違ってきますので、この辺丁寧に。

あと、pkですが。「id」ってカラム名が個人的に嫌いなので、ちゃんと「テーブル名_id」など、見分けが付きやすいものにしています。まぁこの辺は好みではあります。

で、今回はテストでもあるので、テスト用データを。別ファイルに以下のsqlを入れておきます。ファイル名は testdata.sql としておきましょう。

    -- テスト用SQL
    -- SQL一式(認証系除く)
    
    -- まず文字コードを指定
    SET NAMES utf8;
    
    -- ダミーデータ投入
    TRANCATE sales_receipt;
    INSERT INTO sales_receipt SET sales_receipt_id='1', user_id='a', account_title_id='1', amount='3177', sales_receipt_date='2013/1/1 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='2', user_id='a', account_title_id='2', amount='1782', sales_receipt_date='2013/1/2 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='3', user_id='a', account_title_id='3', amount='2354', sales_receipt_date='2013/1/3 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='4', user_id='a', account_title_id='1', amount='3832', sales_receipt_date='2013/1/4 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='5', user_id='a', account_title_id='2', amount='493', sales_receipt_date='2013/1/5 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='6', user_id='b', account_title_id='3', amount='1111', sales_receipt_date='2013/1/6 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='7', user_id='b', account_title_id='1', amount='2783', sales_receipt_date='2013/1/7 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='8', user_id='b', account_title_id='2', amount='3981', sales_receipt_date='2013/1/8 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='9', user_id='b', account_title_id='3', amount='3176', sales_receipt_date='2013/1/9 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='10', user_id='b', account_title_id='1', amount='3447', sales_receipt_date='2013/1/10 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='11', user_id='c', account_title_id='2', amount='3827', sales_receipt_date='2013/1/11 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='12', user_id='c', account_title_id='3', amount='819', sales_receipt_date='2013/1/12 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='13', user_id='d', account_title_id='4', amount='100', sales_receipt_date='2013/1/13 0:00';
    INSERT INTO sales_receipt SET sales_receipt_id='14', user_id='d', account_title_id='5', amount='891', sales_receipt_date='2013/1/14 0:00';

## SQL文の組み立て方(非推奨)
DBハンドルのインスタンスん中にある、escapeメソッドを使ってください。

      // 入力されたと仮定するIDの設定
      $id = '10';
      $id = "' or 1 = 1; --"; // テスト用
    
      // SELECT文の作成
      $sql = "SELECT * FROM sales_receipt WHERE sales_receipt_id = '" . $dbh->escape($id) . "';";
    //var_dump($sql);


## プリペアドステートメントつかった組み立て方(推奨)
mw_sqlというクラスがあるので、それを使ってください。

      // 入力されたと仮定するIDの設定
      $id = '10';
      //$id = "' or 1 = 1; --"; // テスト用
    
      // SELECT文の作成
      $sql = 'SELECT * FROM sales_receipt WHERE sales_receipt_id = :id ;';
    //var_dump($sql);
      // mw_sqlインスタンスを生成
      $mw_sql = new mw_sql();
      // XXX わざと順番を逆に。sql文の設定とbindは、どっちが先でもOKです。なので「動的にパラメタが変更する時」に楽な作りです。
      $mw_sql->bind(':id', $id, data_clump::DATATYPE_STRING);
      //
      $mw_sql->set_sql($sql);


## selectの時のぶん回し方
DBハンドルインスタンスに、sql文(string)またはmw_sqlインスタンス(object)を、queryメソッドで引き渡してください。

### 非推奨なやり方(type=mysqlの時はこちら)

      // 数値添字の配列として行を得る場合
      $res = $dbh->query($sql);
      while($res->fetch()) {
        // 行全体を取得
        $row = $res->get_row();
    var_dump($row);
        // 1つめのデータを取得
        $s = $res->get_data(0);
    var_dump($s);
      }
    
    
      // 連想配列として行を得る場合
      $res2 = $dbh->query($sql);
      $res2->set_fetch_type_hash();
      while($res2->fetch()) {
        // 行全体を取得
        $row = $res2->get_row();
    var_dump($row);
        // IDを取得
        $s = $res2->get_data('sales_receipt_id');
    var_dump($s);
      }


### 推奨するやり方(type=pdo_mysqlの時はこちら)
とりあえず、mw_sql.incを取り込んでください。

    require_once('mw_sql.inc');

コードは以下になります。まぁぶっちゃけ「queryの引数としてmw_sqlインスタンスを渡す」以外、なんにも変わりません。

      // 数値添字の配列として行を得る場合
      $res = $dbh->query($mw_sql);
      while($res->fetch()) {
        // 行全体を取得
        $row = $res->get_row();
    var_dump($row);
        // 1つめのデータを取得
        $s = $res->get_data(0);
    var_dump($s);
      }
    
    
      // 連想配列として行を得る場合
      $res2 = $dbh->query($mw_sql);
      $res2->set_fetch_type_hash();
      while($res2->fetch()) {
        // 行全体を取得
        $row = $res2->get_row();
    var_dump($row);
        // IDを取得
        $s = $res2->get_data('sales_receipt_id');
    var_dump($s);
      }

まとめると。
* SQLを組み立てる(stringまたはmw_sqlクラスを用いて)
* db_handle#queryメソッドでdb_dataインスタンスを取得。渡すのは、mw_sqlインスタンス、またはsql文字列
* 連想配列形式でデータが欲しい場合、あらかじめ、db_data#set_fetch_type_hashを呼んでおく
* fetchでデータ取得。returnはbooleanなので、trueである間中データが取得できる
* データ一つを入手するならget_dataメソッド、行全部を取得するならget_rowメソッドを使う

こんな感じです。

## insertの時のエラー判定
失敗時に、NULLを返してきますので、それで確認をとってみてください。正常終了の場合、db_dataインスタンスがreturnされます、が、特に何かに使うものでもありません。

## update / delete の時の影響行数確認
SQL成功時に帰ってくる db_dataインスタンスに対して affected_rows メソッドを発行します。


## そもそも「SQL文にミスがある」ケース
書式ミス以外に「カラムがない」とか「テーブル作り忘れ」とか色々あると思うんで。

queryメソッドのreturnにはNULLが帰ってくるんで、dbハンドルに対して get_error_message メソッドを発行してみてください。

## サンプルの場所
プリペアドステートメント使用    
<https://github.com/gallu/MagicWeaponManual/tree/master/Db2>

エスケープ処理使用    
<https://github.com/gallu/MagicWeaponManual/tree/master/DbOld2>
