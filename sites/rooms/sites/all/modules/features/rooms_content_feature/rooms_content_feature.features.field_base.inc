<?php
/**
 * @file
 * rooms_content_feature.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function rooms_content_feature_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_room'
  $field_bases['field_room'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_room',
    'foreign keys' => array(
      'rooms_units' => array(
        'columns' => array(
          'target_id' => 'unit_id',
        ),
        'table' => 'rooms_units',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'standart_doubles' => 'standart_doubles',
        ),
      ),
      'target_type' => 'rooms_unit',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'rooms_booking_unit_options'
  $field_bases['rooms_booking_unit_options'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'rooms_booking_unit_options',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'rooms',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'rooms_options',
  );

  // Exported field_base: 'unit_description_description'
  $field_bases['unit_description_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'unit_description_description',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Unit type description',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'unit_description_image'
  $field_bases['unit_description_image'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'unit_description_image',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'label' => 'Image',
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  return $field_bases;
}
