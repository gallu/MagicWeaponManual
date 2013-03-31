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
require_once('mw_sql.inc');

class mw_index extends base_model {

public function execute() {

  // DBハンドルの取得
  $dbh = $this->get_db();
//var_dump($dbh);

  // 入力されたと仮定するIDの設定
  $id = '10';
  //$id = "' or 1 = 1; --"; // テスト用

  // SELECT文の作成
  $sql = 'SELECT * FROM sales_receipt WHERE sales_receipt_id = :id ;';
//var_dump($sql);
  // mw_sqlインスタンスを生成
  $mw_sql = new mw_sql();
  // XXX わざと順番を逆に。sql文の設定とbindは、どっちが先でもOKです。なので「動的にパラメタが変更する時」に楽な作りです。
  $mw_sql->bind(':id', $id, data_clump::DATATYPE_STRING);
  //
  $mw_sql->set_sql($sql);


  // 数値添字の配列として行を得る場合
  $res = $dbh->query($mw_sql);
  while($res->fetch()) {
    // 行全体を取得
    $row = $res->get_row();
var_dump($row);
    // 1つめのデータを取得
    $s = $res->get_data(0);
var_dump($s);
  }


  // 連想配列として行を得る場合
  $res2 = $dbh->query($mw_sql);
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
  $sql_insert = 'INSERT INTO sales_receipt SET sales_receipt_id=:sales_receipt_id, user_id=:user_id, account_title_id=:account_title_id, amount=:amount, sales_receipt_date=:sales_receipt_date ;';
  $mw_sql = new mw_sql();
  $mw_sql->set_sql($sql_insert);
  $mw_sql->bind(':sales_receipt_id', '15', data_clump::DATATYPE_STRING);
  $mw_sql->bind(':user_id'         , 'd' , data_clump::DATATYPE_STRING);
  $mw_sql->bind(':account_title_id', '5' , data_clump::DATATYPE_STRING);
  $mw_sql->bind(':amount'          , 891 , data_clump::DATATYPE_INT);
  $mw_sql->bind(':sales_receipt_date', '2013/1/14 0:00', data_clump::DATATYPE_DATE);

  $r = $dbh->query($mw_sql);
var_dump($r);

  // insert異常系
  $r = $dbh->query($sql_insert);
var_dump($r);

  // update影響行把握
  $sql_update = 'UPDATE sales_receipt SET amount=:amount WHERE sales_receipt_id=:sales_receipt_id ;';
  $mw_sql = new mw_sql();
  $mw_sql->set_sql($sql_update);
  $mw_sql->bind(':sales_receipt_id', '15', data_clump::DATATYPE_STRING);
  $mw_sql->bind(':amount'          , 9999, data_clump::DATATYPE_INT);
  //
  $res = $dbh->query($mw_sql);
var_dump($res);
  $effect_num = $res->affected_rows();
var_dump($effect_num);

  // delete影響行把握
  $sql_delete = "DELETE FROM sales_receipt WHERE sales_receipt_id=:sales_receipt_id ;";
  $mw_sql = new mw_sql();
  $mw_sql->set_sql($sql_delete);
  $mw_sql->bind(':sales_receipt_id', '15', data_clump::DATATYPE_STRING);
  //
  $res = $dbh->query($mw_sql);
var_dump($res);
  $effect_num = $res->affected_rows();
var_dump($effect_num);

  // SQL文に間違いがあるケース
  $sql = 'SLECT * FROM sales_receipt WHERE sales_receipt_id = :id ;';
//var_dump($sql);
  $mw_sql = new mw_sql();
  $mw_sql->bind(':id', $id, data_clump::DATATYPE_STRING);
  $mw_sql->set_sql($sql);
  //
  $res = $dbh->query($mw_sql);
var_dump($res);
var_dump($dbh->get_error_message());

  //
  $conv = $this->get_conv();
  $conv->monoDic('message', 'Hello World.');
}

} // end of class

