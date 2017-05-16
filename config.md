# 環境依存config系(config.confとかdb.confとか)のやり方

「開発環境」と「本番環境」、或いは「front」と「管理画面」でconfigを切り分ける方法をレクチャーします。

## db.confについて

DB接続ハンドルは、どちらかというと「開発と本番で異なる」「frontと管理画面は同じDBハンドルを使っている」ケースが多いかと思うので。
その場合、「環境依存baseと環境共通baseのやり方、index.phpの実践的な書き方 <https://github.com/gallu/MagicWeaponManual/blob/master/base.md> 」でも少し扱いましたが、シンボリックリンクを使った解決法、が楽かと思われます。
具体的には

+ db_dev.conf(開発用)とdev_re.conf(本番用)のファイルを用意する
+ lnコマンドを使って、db.confをシンボリックリンクとして作成(開発環境なら "ln -s db_dev.conf db.conf"、本番環境なら "ln -s db_re.conf db.conf")

とやっておくと、簡単にDBの向き先が切り替えられます。
ちなみに応用として「１台のマシンで複数の個人開発環境」で「個人毎にdatabaseを切っている」ようなケースの場合、db_アカウント名.confを作成して…なんて方法も可能なので、色々と試してみてください。

## config.confについて

こちらはあまり環境には依存せず、「frontと管理画面で異なったり共通だったりする」設定を書く場所になるかと思います。
典型的な所としては…

+ テンプレートファイルの設置ディレクトリは「frontと管理画面で異なる」
+ mapファイルは「frontと管理画面で異なる」
+ DB設定ファイル(DB接続情報)は「frontと管理画面で同じ」
+ 共通ルーチンが入っているPathは「frontと管理画面で同じ」

な事が多いのではないでしょうか？
これも慣習ではあるのですが

+ frontのconfigのファイル名は「config.conf」
+ 管理画面のconfigのファイル名は「admin_config.conf」

である事が多いです。base_environmental-non-dependent.incの
```
// config
$config       = $bp . 'conf/config.conf';
$admin_config = $bp . 'conf/admin_config.conf';
```
で指定している感じですね。

で、「frontと管理画面で共通の設定」は、上述２つのconfigに
```
# 固有、または管理とfrontでのconfigのinclude
@include_wbp('conf/common.conf')
```
と書いた上で、common.confに書いておくとDRYな感じでよいですね。

ちなみに「githubでpublicレポジトリ使ってて、かつ接続トークンなどの秘密情報がある」場合、別途「secret.conf」というのを作っておいて
```
# 固有、または管理とfrontでのconfigのinclude
@include_wbp('conf/secret.conf')
@include_wbp('conf/common.conf')
```
こんな風に取り込む方法もあります。
この場合「.gitignoreのお話 <https://github.com/gallu/MagicWeaponManual/blob/master/gitignore.md> 」で書きますが、「secret.confをcommit対象外にする」事で、秘密情報をガードしていったりします。

## 入出力文字コード

文字コードの指定は

+ 内部エンコード
+ 入出力エンコード

の２つが指定可能です。
内部エンコード(inside_encoding_type)は、よっぽどの理由が無い限りはUTF-8にしておくことを強く強く強くお勧めします。
入出力エンコード(output_encoding_type)も、昨今の風潮的にはUTF-8。
ただ「ガラケーとスマホを１本のコードで」みたいな時は、autoって指定が可能で、これは「ガラケーならsjis、それ以外ならUTF8」って指定になるので、便利ではあります。

## 定数について

定数については…configに書いてもよいのですが、個人的にはあんまり好まないですね。
「多くのプログラムで幅広く使う」上に「どこのクラスに所属するもんでもない」のであればまぁconfigですが、基本的に多くの定数は「どこかのクラスに所属可能」であるケースが多いかと思うので。
どちらかというと「クラス定数」にまとめたほうがわかりやすいと思います(defineで数千行とかいうのを幾たびかメンテナンスしているので、「定数ファイル」ってあんまりイケテナイって思ってるんですよね…)。

## サンプルについて

「環境依存baseと環境共通baseのやり方、index.phpの実践的な書き方」「環境依存config系(config.confとかdb.confとか)のやり方」「(改めて)diのお話」「.gitignoreのお話」「フレームワークの置き場所とpluginの置き場所」の中に出てきた記述は、一式まとめて「上述を総括して、デフォルトにしやすい「空っぽのプロジェクト」」<https://github.com/gallu/MagicWeaponManual/blob/master/empty_project.md> にサンプルファイルを置いてあるので、記述の詳細はこちらを確認してください。

