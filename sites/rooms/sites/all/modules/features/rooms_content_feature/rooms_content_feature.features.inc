<?php
/**
 * @file
 * rooms_content_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function rooms_content_feature_node_info() {
  $items = array(
    'unit_description' => array(
      'name' => t('Unit Description'),
      'base' => 'node_content',
      'description' => t('Bookable Unit Description.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_default_rooms_booking_type().
 */
function rooms_content_feature_default_rooms_booking_type() {
  $items = array();
  $items['standard_booking'] = entity_import('rooms_booking_type', '{
    "type" : "standard_booking",
    "label" : "Standard Booking",
    "weight" : "0",
    "data" : null,
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_rooms_unit_type().
 */
function rooms_content_feature_default_rooms_unit_type() {
  $items = array();
  $items['standart_doubles'] = entity_import('rooms_unit_type', '{
    "type" : "standart_doubles",
    "label" : "Standart Doubles",
    "weight" : "0",
    "data" : {
      "base_price" : "100",
      "min_sleeps" : "1",
      "max_sleeps" : "2",
      "min_children" : "0",
      "max_children" : "1",
      "rooms_description_source" : ""
    },
    "rooms_booking_unit_options" : { "und" : [
        { "name" : "Tv", "quantity" : "1", "operation" : "add", "value" : "5" },
        {
          "name" : "Fridge",
          "quantity" : "1",
          "operation" : "add-daily",
          "value" : "10"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
