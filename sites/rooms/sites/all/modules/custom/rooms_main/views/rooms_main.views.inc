<?php
// This file must be at mymodule/views directory.

/**
 * @file
 * Views definitions for mymodule module.
 */

/**
 * Implements hook_views_data().
 */

function rooms_main_views_data() {
  $data = array();
  $data['rooms_units']['book_it'] = array(
    'title' => t('Book it'),
    'help' => t('Book room.'),
    'field' => array(
      'handler' => 'rooms_main_handler_book_it',
    ),
  );
  
  /*$data['rooms_bookings']['book_it'] = array(
    'title' => t('test'),
    'help' => t('Book room.'),
    'field' => array
      'handler' => 'mymodule_handler_handlername',
    ),
  );*/
  return $data;
}
