# DBにつなげてみる
WebアプリでDBに繋がらないってのもなかなかにない状態なので。

お作法込みで、MagicWeapon流の使い方を説明していきます。

## 設定情報の保存
必須ではないんですが、やっておいたほうがよいので。

dbinfoってディレクトリを作ります。このディレクトリは「プログラム中には一切使わないけど、ドキュメントとして保存しておく」諸々です。    
プログラム中は使わないけど「開発お作法的にはちょくちょく使う」ので、そんな感じでイメージしてください。

dbinfoの中に、setup.txt ってファイルを作ります。

    create database mw_db_test;
    grant ALTER, CREATE, DELETE, DROP, INDEX, INSERT, LOCK TABLES, SELECT, UPDATE on mw_db_test.* to 'mw_db_test'@'localhost' identified by 'Wv[I[:6aBH#Oj57a';
    flush privileges ;

これを一度DBにぶち込んで、databaseとユーザを作成します。

localなプロジェクトであればgitの管理対象に、githubとかに持ち上げるんであれば対象外にしたいので、.gitignore に書いて、管理対象外としましょう。

今回は説明もあるんで、githubに持ち上げておきます(パスワードは変えてるけどね B-p)。

### Q:「別所でドキュメントに書いておけばよくない？」
A: 無くすでしょ？ メンテナンス怠るでしょ？ ほかのプログラムと混ぜて、わけわかめな状態にするでしょ？

一カ所にまとめておいた方が、安全なケースが多いのですよ、現実問題として。


## DBハンドルの取得方法

### 設定(db.conf)
configに設定をして、db.confに細かい設定を書いておきます。

configの追加はこんな感じ。

    # DB設定
    db_config_path_wbp = conf/db.conf

db.confにはこんな風に書いておきます。db.confって名前なのは以下略。

接続にmysql_connectを使う場合(激しく非推奨)
    # DB設定
    type = mysql
    database = mw_db_test
    user = mw_db_test
    pass = Wv[I[:6aBH#Oj57a
    host = localhost
    #port = 
サンプルコード：    
<>

接続にPDOを使ってmysqlにつなげる場合
    # DB設定
    type = pdo_mysql
    database = mw_db_test
    user = mw_db_test
    pass = Wv[I[:6aBH#Oj57a
    host = localhost
    #port = 
サンプルコード：    
<>

PostgreSQLは一時期対応していたのですが、最近全然扱わない＆少し修正が入ってるので、ぶっちゃけ「動くかどうか」も不明です。

要望があったら(それ以外のDBも含め)対応を前向きに検討しますので、ご連絡などいただけるとありがたいです。

### メソッド(model#get_db())
modelでDBハンドルを使う時は、以下のようにしてハンドルを取得します。

      // DBハンドルの取得
      $dbh = $this->get_db();
    var_dump($dbh);

あぁ念のため。インスタンスの中のパスワードは、意図的に「----」に書き直してあります。いくらvar_dumpでも、生パスワードが見え見えとか、嫌でしょ？

### エラーの補足
DB接続とかでエラーが出てきたときは、$dbh->get_error_message()、である程度把握できると思うので、そのようにお願いいたします。

## どうしても「生のDBハンドルが欲しい人」用のやり方草案
base_model_baseのinitializeメソッドをオーバライドして実装するとよろしいかと思います。読み進むとinitializeメソッドの話が出てくるんで、その辺で。

…うんまぁdbハンドルクラスに「get_raw_dbhandle()」とかってメソッド作ってもよいのですが…現状想定では「いらない」しなぁ、と。安全性の担保がききにくいんで、MagicWeaponのお作法的に則った形で「かつ」必要性がある、って感じなら実装しまふ。

## 文字化けするときの対策：プログラム側関数で片付けず、Mysqlのclientの設定で片付けましょう
基本、MagicWeaponは「餅は餅屋」って考え方なので。

DBの文字化けは、MySQLならmy.cnfあたりでの対応をまず考えましょう。場当たりな対応はやったことあるし方法がないわけではないのですが、いろいろとおすすめしないので。

やり方に気づいた人は、或いは自力で編み出せる人は適宜やってくださいませ。
