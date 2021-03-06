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

  // DBハンドルの取得
  $dbh = $this->get_db();
//var_dump($dbh);

  // 入力されたと仮定するIDの設定
  $id = '10';
  //$id = "' or 1 = 1; --"; // テスト用

  // SELECT文の作成
  $sql = "SELECT * FROM sales_receipt WHERE sales_receipt_id = '" . $dbh->escape($id) . "';";
//var_dump($sql);

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

  // insert正常系
  // XXX 面倒なんでべたうちしてますが、実際にはちゃんと「値をいちいちescapeして」文字列組み立ててくださいませ
  $sql_insert = "INSERT INTO sales_receipt SET sales_receipt_id='15', user_id='d', account_title_id='5', amount='891', sales_receipt_date='2013/1/14 0:00';";
  $r = $dbh->query($sql_insert);
var_dump($r);

  // insert異常系
  $r = $dbh->query($sql_insert);
var_dump($r);

  // update影響行把握
  $sql_update = "UPDATE sales_receipt SET amount='9999' WHERE sales_receipt_id='15'";
  $res = $dbh->query($sql_update);
  $effect_num = $res->affected_rows();
var_dump($effect_num);

  // delete影響行把握
  $sql_delete = "DELETE FROM sales_receipt WHERE sales_receipt_id='15';";
  $r = $dbh->query($sql_delete);
var_dump($r);

  // SQL文に間違いがあるケース
  $sql = "SLECT * FROM sales_receipt WHERE sales_receipt_id = '" . $dbh->escape($id) . "';";
//var_dump($sql);
  //
  $res = $dbh->query($sql);
var_dump($res);
var_dump($dbh->get_error_message());

  //
  $conv = $this->get_conv();
  $conv->monoDic('message', 'Hello World.');
}

} // end of class

