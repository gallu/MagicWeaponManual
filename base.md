#  環境依存baseと環境共通baseのやり方、index.phpの実践的な書き方

実践的なbase.incファイルの作り方、index.php(admin.php)の書き方について学んでいきます。

## base.incで困ること

base.inc自体は、 <https://github.com/gallu/MagicWeaponManual/blob/master/helloworld.md> でも出てきました。
他に困ることがなければこのままでもいいのですが…実際には、些か困るシーンが出てきます。
業務では、大抵の場合「front(ユーザ用)画面」と合わせて「管理画面」が必要になります。ECショップで複数店舗があったりすると、これが「front画面」「店舗管理画面」「全体管理画面」で３種類必要だったりもします。

具体的には「開発環境と本番環境との差異」があります(もう一つ「frontと管理画面で異なるもの」と「frontと管理画面で共通のもの」がありますが、それは次の「configファイル」の章で説明します)。
もちろんそれらを「コピペでどうにかする」のも一つの手ではありますが、コピペを推奨するようなフレームワークはあまりお好みではありません。

というわけで、上述を切り分けていきます。
具体的には

+ 「開発環境と本番環境とで異なる設定」を書いたファイル
+ 「開発環境と本番環境とで共通の設定」を書いたファイル

を用意します。
通常だと

+ 開発環境に依存するファイル：base_dev.inc
+ 本番環境に依存するファイル：base_re.inc
+ 環境共通のファイル：base_environmental-non-dependent.inc

としています。
base_dev.incは、状況にもよりますが

```
<?php

//
ini_set('display_errors', 'on');
error_reporting(E_ALL);

//
//ini_set('display_errors', 'off');

// 基準ディレクトリの設定
$bp = __DIR__ . '/';

//
require_once( $bp . 'base_environmental-non-dependent.inc');

```
と書く事が多いです。

また、base_re.incは

```
<?php

//
//ini_set('display_errors', 'on');
//error_reporting(E_ALL);

//
ini_set('display_errors', 'off');

// 基準ディレクトリの設定
$bp = __DIR__ . '/';

//
require_once( $bp . 'base_environmental-non-dependent.inc');
```

と書く事が多いですね。
共通のほうは、Smartyを使う前提だと

```
<?php

// MWを使えるようにする
$dir = '/opt/www/MagicWeapon/';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);
// Smartyを使えるようにする
$dir = $bp . 'lib/plugin/smarty/libs/';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

// 基本的なphp iniの設定を一式
require_once('mw_set_ini.inc');
// タイムゾーンの設定
date_default_timezone_set('Asia/Tokyo');

/*
// セッション用基本設定群
require_once('mw_session_set_ini.inc');
// PHPセッションの開始
session_start();
*/

// config
$config       = $bp . 'conf/config.conf';
$admin_config = $bp . 'conf/admin_config.conf';

// controller周り
require_once('controller.inc');
//
$co = new controller;
$co->set_base_path($bp);
```

こんな感じになります(Smartyをインストールしてある先の「lib/plugin/」ディレクトリについては、後述する「フレームワークの置き場所とpluginの置き場所 <https://github.com/gallu/MagicWeaponManual/blob/master/plugin.md> 」を確認してください)。
セッション部分はコメントアウトしてあるのですが、使うようでしたら適宜コメントを外してください。

後は必要に応じて、base_[dev|re].incなりbase_environmental-non-dependent.incなりに「必要な設定や処理」を最低限追記していくと、そんなに散らからないかと思います。

最後に。
index.phpでは

```
// 基本設定の読み込み
require_once('../base.inc');
```

と読み込んでいるので、base.incを作ります。
具体的には「lnコマンドでシンボリックリンクを作成」します。

基準ディレクトリにいる前提で、開発環境であれば

```
ln -s base_dev.inc base.inc
```

というコマンドを一度だけ発行。
本番環境であれば

```
ln -s base_re.inc base.inc
```

というコマンドを一度だけ発行します。
これによって「index.phpではbase.incを読み込んでいる」のですが、実際には「開発環境ならbase_dev.incを、本番環境ならbase_re.incを読み込んでいる」という風になります。

ちなみにこの「シンボリックリンクによる切り替え」は割とよくつかっていて、具体的には、Smartyも本当は「lib/smarty-3.1.29/」にあるのですが、シンボリックリンクを切って「lib/smarty/」で見れるようにしてあります( コマンド例：ln -s smarty-3.1.29 smarty )。
これをやっておくと「バージョンアップが楽」なのに加えて「万が一の時にすぐに元に戻せる」ので、色々と便利です。
blog記事「■[我留流][その他技術]シンボリックリンク関連２種 <http://d.hatena.ne.jp/gallu/20120724/p1> 」を見ていただくと多少わかりやすいか、と。

## 基準ディレクトリのお話し

以前の記述では

```
// 基準ディレクトリの設定
$bp = '/home/furu/work/MagicWeaponManual/HelloWorld/';
```

という風に、絶対パスを書いていたかと思います。
…いやこれはこれでよいのですが、開発環境の構築状況(例： <http://d.hatena.ne.jp/gallu/20120725/p1> のような形で「１台のマシンに複数の個人開発環境を用意」など)によっては些か面倒にもなるので。
「base*.incファイルを基準ディレクトリ直下に置く」というルールが前提ではありますが、実際には

```
// 基準ディレクトリの設定
$bp = __DIR__ . '/';
```

のほうが圧倒的に「楽」」なので、特に弊害が無い限り、現在はこの方法を推奨しています。

## サンプルについて

「環境依存baseと環境共通baseのやり方、index.phpの実践的な書き方」「環境依存config系(config.confとかdb.confとか)のやり方」「(改めて)diのお話」「.gitignoreのお話」「フレームワークの置き場所とpluginの置き場所」の中に出てきた記述は、一式まとめて「上述を総括して、デフォルトにしやすい「空っぽのプロジェクト」」<https://github.com/gallu/MagicWeaponManual/blob/master/empty_project.md> にサンプルファイルを置いてあるので、記述の詳細はこちらを確認してください。

