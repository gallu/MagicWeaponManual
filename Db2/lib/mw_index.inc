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

  // DBƒnƒ“ƒhƒ‹‚ÌŽæ“¾
  $dbh = $this->get_db();
var_dump($dbh);

  //
  $conv = $this->get_conv();
  $conv->monoDic('message', 'Hello World.');

}

} // end of class

