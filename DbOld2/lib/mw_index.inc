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

  // DB�n���h���̎擾
  $dbh = $this->get_db();
//var_dump($dbh);

  // ���͂��ꂽ�Ɖ��肷��ID�̐ݒ�
  $id = '10';
  //$id = "' or 1 = 1; --"; // �e�X�g�p

  // SELECT���̍쐬
  $sql = "SELECT * FROM sales_receipt WHERE sales_receipt_id = '" . $dbh->escape($id) . "';";
//var_dump($sql);

  // ���l�Y���̔z��Ƃ��čs�𓾂�ꍇ
  $res = $dbh->query($sql);
  while($res->fetch()) {
    // �s�S�̂��擾
    $row = $res->get_row();
var_dump($row);
    // 1�߂̃f�[�^���擾
    $s = $res->get_data(0);
var_dump($s);
  }


  // �A�z�z��Ƃ��čs�𓾂�ꍇ
  $res2 = $dbh->query($sql);
  $res2->set_fetch_type_hash();
  while($res2->fetch()) {
    // �s�S�̂��擾
    $row = $res2->get_row();
var_dump($row);
    // ID���擾
    $s = $res2->get_data('sales_receipt_id');
var_dump($s);
  }

  // insert����n
  // XXX �ʓ|�Ȃ�łׂ��������Ă܂����A���ۂɂ͂����Ɓu�l����������escape���āv������g�ݗ��ĂĂ��������܂�
  $sql_insert = "INSERT INTO sales_receipt SET sales_receipt_id='15', user_id='d', account_title_id='5', amount='891', sales_receipt_date='2013/1/14 0:00';";
  $r = $dbh->query($sql_insert);
var_dump($r);

  // insert�ُ�n
  $r = $dbh->query($sql_insert);
var_dump($r);

  // update�e���s�c��
  $sql_update = "UPDATE sales_receipt SET amount='9999' WHERE sales_receipt_id='15'";
  $res = $dbh->query($sql_update);
  $effect_num = $res->affected_rows();
var_dump($effect_num);

  // delete�e���s�c��
  $sql_delete = "DELETE FROM sales_receipt WHERE sales_receipt_id='15';";
  $r = $dbh->query($sql_delete);
var_dump($r);

  // SQL���ɊԈႢ������P�[�X
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
