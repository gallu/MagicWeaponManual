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

