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

###config
###map
##modelクラスを用意する
##表示してみる
##プログラムの流れのおさらい
