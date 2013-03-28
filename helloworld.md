#まずはざっくりとHello World
ドが付くほど最低限の実装で、まずはプログラムの基本中の基本「Hello World」を表示させてみましょう。

##MagicWeaponの設置
適当に取得してきて、お好みのディレクトリに展開してください。

一端便宜上、ここでは「 /opt/www/MW/ 」のディレクトリにMagicWeaponのソースを一式展開した、と仮定します。

楽に行くなら、展開したいディレクトリの一つ上(上述の場合、 /opt/www の位置)で
    git clone git://github.com/gallu/MagicWeapon.git MW
とかでマルっと取得してくださいませ。

##いわゆる「プロジェクト」のディレクトリを切る
とりあえず、適当に「基準になるディレクトリ」を作成してください。この基準ディレクトリ以下のソースコードが、基本的に「gitやらsvnやらで管理対象にする」ファイル群になります。

便宜上、おいちゃんは「 /home/furu/work/MagicWeaponManual/HelloWorld/ 」を基準ディレクトリにします。

###大まかな、各ディレクトリの意味
基準ディレクトリに、最低限以下のディレクトリを作成してください。

conf
: 各種設定ファイルを格納する領域です

lib
: 自分で書くコードを一式置いておく場所です

template
: テンプレートファイルの格納場所です

wwwroot
: httpd.conf, nginx.confなどに書く、DocumentRoot用のディレクトリです

##base.incの用意と設定
基準ディレクトリ直下に「base.inc」ってファイルを用意します。

中身ですが、一端「以下をそのまま」利用していただけると。あぁ「MagicWeaponのインストールディレクトリ」と「基準ディレクトリ」は、ちゃんと適切なものに置き換えてくださいませ。

    <?php
    
    //
    ini_set('display_errors', 'on');
    error_reporting(E_ALL);
    //
    //ini_set('display_errors', 'off');
    
    // MWを使えるようにする
    $dir = '/opt/www/MW';
    set_include_path(get_include_path() . PATH_SEPARATOR . $dir);
    
    // 基本的なphp.iniの設定各種
    require_once('mw_set_ini.inc');
    
    // 基準ディレクトリの設定
    $bp = '/home/furu/work/MagicWeaponManual/HelloWorld/';
    
    // configファイル名
    $config       = $bp . 'conf/config.conf';
    
    //
    require_once('controller.inc');
    
    //
    $co = new controller;
    $co->set_base_path($bp);

## マウントポイントになるindex.phpを用意する
これも、以下のソースをそのまま利用してください。置き場所はwwwrootの中になります。

    <?php
    
    //
    require_once('../base.inc');
    //
    $co->set_config($config);
    
    //
    $co->run();

##configに最低限を設定する
最低限の設定は２つ、config.confファイルとmap.txtファイルになります。

ちなみに、config.confファイルがそのような名前になっている理由は「上述、base.incん中でそういうファイル名にしたから」で、map.txtファイルがそのような名前になっている理由は「これから書くconfig.confファイルでそういうファイル名にするから」です。特に、他意もハードコーディングも存在しません。

いつものパターンですが、以下の２つを、confディレクトリにぶち込んでください。

###config
    #
    # configファイル
    #
    ################################
    
    # 文字コード
    inside_encoding_type = UTF-8
    output_encoding_type = UTF-8
    
    # mapファイル
    mapping_file_path_wbp = conf/map.txt
    
    # modelその他のファイルの置き場所
    common_include_dir_wbp = lib/
    
    # テンプレートエンジン設定
    template_dir_wbp = template/
    template_encoding_type = UTF-8


###map
    # top page
    index     =  mw_index.inc:mw_index index.tpl

##modelクラスを用意する
よそ様のフレームワークで言うところの「ページコントローラ」的なものを用意します。MagicWeaponだと「model」って言います。

libディレクトリの中に、mw_index.incってファイル名で作成をしてください。このファイル名＆このクラス名になっている理由は「map.txtファイルにそう書いた」からです。

    <?php
    /***************************************************
     * Hello world Top Page
     *
     * @package
     * @access  public
     * @author
     * @create
     * @version
     ***************************************************/
    
    require_once('base_model.inc');
    
    class mw_index extends base_model {
    
    public function execute() {
    }
    
    } // end of class


##templateファイルを用意する
もうちょっとですねぇ。最後は「表示するHTMLテンプレート」を用意します。とはいえ、今回は特に「動的に置換する」ものでもないので、まぁざっくりと。

ファイルは、templateディレクトリの中に、index.tplのファイル名でお願いします。また、ファイルはUTF-8で保存してください。

「templateディレクトリに格納」＆「テンプレートファイルはUTF-8」ってのはconfig.confに書いてあるからで、「ファイル名がindex.tpl」ってのはmap.txtに書いてあるから、です。

    <!DOCTYPE HTML>
    <html lang="ja">
    <head>
    <meta charset="UTF-8">
    <title>MagicWeapon HelloWorld.</title>
    </head>
    <body>
    HelloWorld.
    </body>
    </html>

##表示してみる
DocumentRootを適切にみつつ、確認をしてみてください。

たぶん時々不意のメンテナンスをしていますが、そうでないタイミングなら、以下のURIで見ていただくことも可能です。    
<http://www.m-fr.net/MagicWeaponManual/HelloWorld/index.php>

なお、上述一式は、githubの中にあるので、動かない場合は適宜見比べるなりdiffるなり目diffるなりしてみてください。    
<https://github.com/gallu/MagicWeaponManual/tree/master/HelloWorld>


##プログラムの流れのおさらい
動くようになったところで、大まかに流れの確認をしてみましょう。

* index.phpがcallされます。index.phpではbase.incを取り込んで、基準ディレクトリやらconfigファイルの位置やらを把握します。
* index.phpから、controllerクラスを生成。このタイミングで、必要なインスタンスがいろいろ作られます。今回は「このタイミングでテンプレートエンジンクラスのインスタンスが生成されること」だけ認識してください。デフォルトは、MagicWeaponの手持ちのテンプレートエンジン「secure_conv」が選択されます(あとで、Smartyへの置き換えをやります)
* index.phpからrunが実行されます
* controller#runでは、「ディスパッチャ」が走ります
* c=で与えられたコマンド名を解決します。省略された場合(今回がそうですね)は、コマンド名はindexである、と認識します
* コマンド名をkeyに、mapファイル(map.txt)をチェックします
* mapファイルに書いてあるファイルをincludeして、書いてあるクラス名をnew。そのインスタンスに対してexecuteメソッドをcallします
* 上述の流れで、mw_index.incの中にあるmw_indexのインスタンスが生成され、executeが動きました。今回は処理なしですが。
* 処理がcontrollerに戻ります。modelでの処理が終わると、次にviewクラスを生成し、実行に移ります
* viewクラスは大まかに「modelの中にあるテンプレートエンジンインスタンスを用いて、置換＆出力を行います」。なお、ここで用いられるテンプレートファイル名は「modelで特に指定したもの」または「指定がない場合、mapファイルに書いてあるテンプレートファイル名」となります

大まか、こんな感じですね。

ここから結構作り替えをしていきますので、まずは「初手の流れ」をしっかり把握しておいてください。
