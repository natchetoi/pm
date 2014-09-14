<?php

/**
 * @file
 * Definition of rooms_main_handler_book_it.
 */

/**
 * Description of what my handler does.
 */
class rooms_main_handler_book_it extends rooms_unit_handler_link_field {
  /**
   * Add some required fields needed on render().
   */
  function construct() {
    parent::construct();
    $this->additional_fields['field_something'] = array(
      'table' => 'field_data_field_something',
      'field' => 'field_something_value',
    );
  }

  /**
   * Renders the field handler.
   */
  function render($values) {
    $unit_id = $values->{$this->aliases['unit_id']};

    return 'test';

  }
}
