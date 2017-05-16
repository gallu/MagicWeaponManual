# (改めて)diのお話

## 書き方のおさらい

以前に「テンプレートエンジン使ってHello World <https://github.com/gallu/MagicWeaponManual/blob/master/templateengine_first.md> 」でも少し使いましたが、簡単におさらいをしてみます。
まず、config.conf(またはadmin_config.conf)に、以下の行を追記します。
```
# DIコンテナ設定
di_config_wbp = /conf/di.conf

```

続いて、di.confを記述していきます。
記述フォーマットは
```
di識別名 = includeファイル名:newするクラス名
```
というフォーマットになります。
前述のSmartyですと
```
# 置換エンジンはSmarty
template_engine = Smarty.class.php:Smarty
```
という感じでした。
内部的には、ここから
```
$conv = di::create('template_engine');
```
という感じでインスタンスを作成しています。
まぁDI(依存性の注入)というよりは、factoryですね。

上述のテンプレートエンジンの他にも、いくつか「どのクラスを使うか、設定ファイルから注入できる」ものがありますので、確認をしてみると面白いでしょう。
また「自分の書いているコード」の中でも普通に上述は使えますので、使ってみるのも面白いかと思います。

## サンプルについて

「環境依存baseと環境共通baseのやり方、index.phpの実践的な書き方」「環境依存config系(config.confとかdb.confとか)のやり方」「(改めて)diのお話」「.gitignoreのお話」「フレームワークの置き場所とpluginの置き場所」の中に出てきた記述は、一式まとめて「上述を総括して、デフォルトにしやすい「空っぽのプロジェクト」」<https://github.com/gallu/MagicWeaponManual/blob/master/empty_project.md> にサンプルファイルを置いてあるので、記述の詳細はこちらを確認してください。
