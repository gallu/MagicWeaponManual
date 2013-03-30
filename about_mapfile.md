# mapファイルについて
confの中にある、map.txtの書式とその背景にある哲学、について。

## 基本的な表記の方法
コマンド名 = includeするファイル名:newするクラス名 テンプレートファイル名

なので、
    index     =  mw_index.inc:mw_index index.tpl
の場合
コマンド名：index    
includeするファイル名：mw_index.inc    
newするクラス名：mw_index    
テンプレートファイル名：index.tpl

となります。

１カラム目#でのコメントが許可されているので、多少はコメントも行けます。

## 省略表記の方法
ん…ありがちなのが、こーゆーケース(実例)。

    item_list = item_list.inc:item_list item_list.tpl

上述は面倒なので、以下の省略が可能。

    item_list = : .

：の前後には空白が必要なので注意のほどを。

## わざわざ明示する理由
いわゆる「一般的なフレームワーク」だと、引数とかパラメタとかに応じて「自動で名前を作って」処理するのですが。
エスケープとかサニタイズとか諸々の処理に抜けがあればディレクトリトラバーサルが発生するし、抜けないように作るのも面倒だし。
一方で「明示的にホワイトリスト化して、なければ動かない」だとそもそもこのポイントでクラックのしようがないので。
思想的に「デフォルト不許可、明記されているもののみ許可」のほうが好みなんで、そーゆー実装になってます。

## 応用編：静的なPage群の出力方法
単純に「静的な出力」だと、modelは１つにして、mapファイルでの量産が可能です。
よくst.incってファイルでstってクラスを作るのですが。

    <?php
    /***************************************************
     * 静的Page出力
     *
     * @package
     * @access  public
     * @author
     * @create
     ***************************************************/
    require_once('base_model.inc');
    
    class st extends base_model {
    
    public function execute() {
    }
    
    } // end of class

これがひとつあると、静的Pageを出す時に、map.txtに列挙するだけでいける。

例
    hoge = st.inc:st hoge.tpl
    foo  = st.inc:st foo.tpl
    bar  = st.inc:st bar.tpl

応用編として「認証されたユーザのみ、静的Pageを出力する」場合は、「認証チェックをするstクラス」を作ればOK。
