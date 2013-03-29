#modelをもうちょっと継承してみる
「HelloWorldConv」をつかって、modelの継承を少し増やすサンプルを書いてみます。また「なんで増やすのか」について理解をしていきます。

サンプルは    
<HelloWorldConv2>
でご覧ください。

## base_model_base.incとbase_model_front_base.incを用意してみる
とりあえず、libの中に「common」ってディレクトリを作成します。大まかに、commonは「共通になるモノ」を入れておく場所です。「ナニを持って共通とするか」については後述。

commonの中に、以下の２つのファイルを用意します。    
まずは base_model_base.inc 。

    <?php
    
    /***************************************************
     * 全体共通
     *
     * @package
     * @access  public
     * @author
     * @create
     ***************************************************/
    
    require_once('base_model.inc');
    
    class base_model_base extends base_model {
    } // end of class

続いて、base_model_front_base.inc 。

    <?php
    
    /***************************************************
     * フロントエンド共通
     *
     * @package
     * @access  public
     * @author
     * @create
     ***************************************************/
    
    require_once('base_model_base.inc');
    
    class base_model_front_base extends base_model_base {
    } // end of class

これに伴って、mw_index.incを以下のように変更します。

    <?php
    
    /***************************************************
     * Hello world Top Page
     *
     * @package
     * @access  public
     * @author
     * @create
     ***************************************************/
    
    
    require_once('base_model_front_base.inc');
    
    class mw_index extends base_model_front_base {
    
    public function execute() {
    
      //
      $conv = $this->get_conv();
      $conv->monoDic('message', 'Hello World.');
    
    }
    
    } // end of class

まぁ継承元のクラス名を変えただけですね。

## わざわざ継承クラスを増やす意味
端的には「サイト全体で共通な処理」「フロントエンド全体で共通な処理」をフックするためです。

まだ作ってませんが、大抵の場合、base_model_front_base.incと同じレベルで、base_model_admin_base.incとか作ります。ショッピングモール系とかだとbase_model_adadmin_base.incも作りますね。

この辺の領域はあらかじめ作っておいた方が手間がないので、通常、MagicWeaponのお作法だと、こうやってmodelを段々にしておいて、後で手を入れやすいようにしています。

