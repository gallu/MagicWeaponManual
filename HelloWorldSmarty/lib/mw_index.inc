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
  //
  $smarty = $this->get_conv();
  $smarty->set('message', 'Hello World.');

}

} // end of class

