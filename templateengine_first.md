# テンプレートエンジン使ってHello World

## テンプレートエンジンを選ぶ
とりあえずデフォルトはMagicWeaponの「secure_conv」というのを使っているのですが。

いやまぁもちろん作ってるので相応に「便利」だとは思ってるんで使ってるんですが(簡単に書くと「テンプレート側にロジックを書くのがほぼ不可能」なので、ロジックとデザインの分離を強制できる)。

ただまぁ現場でのSmarty勢の勢いには壮絶なものもあり。まぁSmartyも「ちゃんとルールを守って最低限の使用にとどめれば」それなりに便利なので、Smarty用の設定について少しふれてみます。

なお、詳細なソースは適宜gitの中をご確認ください。    
CONV対応ソース： <https://github.com/gallu/MagicWeaponManual/tree/master/HelloWorldConv>    
Smarty対応ソース： <https://github.com/gallu/MagicWeaponManual/tree/master/HelloWorldSmarty>    

## CONVの場合の設定と実行
### framework側設定
特段になにも。デフォなので。

### 実装/プログラム側
modelの中に、以下のプログラムを記述します。とりあえず２行にしてますが、１行にまとめても、この程度ならさほど。

get_convでテンプレートエンジンインスタンスがとれるので、monoDicメソッドで文字列(または数値)を設定してください。なお、monoDicは配列には対応していません(後で配列についてはやります)。

      //
      $conv = $this->get_conv();
      $conv->monoDic('message', 'Hello World.');


### 実装/テンプレート側
この一行を入れてください。

    %%%message%%%

### サンプル
<http://www.m-fr.net/MagicWeaponManual/HelloWorldConv/>


## Smartyの場合の設定と実行
### framework側設定
DIを使います。Dependency Injectionとか書いてますが、MagicWeaponのDIはぶっちゃけ「factory」程度のブツになります。

DIの機能を用いるので「configに、diコンフィグのファイルの位置を教える」「diコンフィグを作成する」の２つの段階を踏みます。

また、Smartyを用いるので「元々のSmartyの位置を設定する」「Smartyに必要な最低限の設定を行う(configファイルに書けます)」が必要です。

なんで、「DIを使うのに２手順」「Smarty固有でもう２手順」で、合計４手順が必要になるわけですね。

#### DIを使う
DIは、専用のconfigファイルを使って設定します。ファイル名はdi.confとしますが、これはconfig.confにそう書くからで以下略。

まずconfig.confを修正しましょう。

    # DIコンテナ設定
    di_config_wbp = /conf/di.conf

次に、di.confを作成して、以下の記述を加えます。

    # 置換エンジンはSmarty
    template_engine = Smarty.class.php:Smarty

ちなみに。上述だと、XSSのセキュリティ的にちょいといろいろ、アレがナニな感じになりますので。MagicWeapon的には、こちらをおすすめします。いやまぁ「自力で作ったラッパー」でもいいんですがね。

    # 置換エンジンはSmarty
    template_engine = mw_smarty.inc:mw_smarty

#### Smartyを使う
大まかに「Smartyがある場所を指定する」のと「Smartyに固有の設定をconfigに書く」の２つになります。

まず「Smartyの場所」ですが、include_pathに加えるのが一番早いと思います。base.incに書き加えてください。当然ですが、ディレクトリ名は自分の環境に合わせてくださいませ。

    // Smartyを使えるようにする
    $dir = '/opt/www/Smarty-3.1.8/libs';
    set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

次に、Smarty用の各種設定です。template_dirはすでにconfig.confで設定されているので、あとはcompile_dirとconfig_dirを設定してやります。

場所はどこでも良いのですが、基準ディレクトリの下に「smarty_wk」というディレクトリを切り、その中に「config」「templates_c」のディレクトリを切りました。templates_cのパーミッションに注意をしておいてくださいませ。

で、上述用のconfigの設定追加です。

    # Smarty用の追加
    smarty_compile_dir_wbp = smarty_wk/templates_c/
    smarty_config_dir_wbp = smarty_wk/config/

### 実装/プログラム側
mw_smartyだと、setってメソッドで「自動的にHTMLエスケープ」が動くので、assignは使わず、setメソッドを用います。

      //
      $smarty = $this->get_conv();
      $smarty->set('message', 'Hello World.');


### 実装/テンプレート側
Smartyの書式そのまんまですが。

    {$message}

### サンプル
<http://www.m-fr.net/MagicWeaponManual/HelloWorldSmarty/>


## その他のテンプレートエンジン
まだ未対応なんですが、たぶん対応はそんなに厄介でもないので。なんか「これ対応して～」ってのがあったらご連絡いただければ。
