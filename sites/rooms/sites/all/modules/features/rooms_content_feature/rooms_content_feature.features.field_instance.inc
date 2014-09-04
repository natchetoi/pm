<?php
/**
 * @file
 * rooms_content_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function rooms_content_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-unit_description-field_room'
  $field_instances['node-unit_description-field_room'] = array(
    'bundle' => 'unit_description',
    'default_value' => array(
      0 => array(
        'target_id' => 1,
      ),
      1 => array(
        'target_id' => 2,
      ),
      2 => array(
        'target_id' => 3,
      ),
      3 => array(
        'target_id' => 4,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_room',
    'label' => 'Room',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 3.1,
    ),
  );

  // Exported field_instance: 'node-unit_description-unit_description_description'
  $field_instances['node-unit_description-unit_description_description'] = array(
    'bundle' => 'unit_description',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'unit_description_list' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'unit_description_description',
    'label' => 'A description of this unit type.',
    'required' => FALSE,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-unit_description-unit_description_image'
  $field_instances['node-unit_description-unit_description_image'] = array(
    'bundle' => 'unit_description',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'unit_description_list' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'unit_description_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 2.1,
    ),
  );

  // Exported field_instance: 'rooms_unit-standart_doubles-rooms_booking_unit_options'
  $field_instances['rooms_unit-standart_doubles-rooms_booking_unit_options'] = array(
    'bundle' => 'standart_doubles',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'rooms',
        'settings' => array(),
        'type' => 'rooms_options_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'rooms_unit',
    'field_name' => 'rooms_booking_unit_options',
    'label' => 'Options',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'rooms',
      'settings' => array(),
      'type' => 'rooms_options_combined',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A description of this unit type.');
  t('Image');
  t('Options');
  t('Room');

  return $field_instances;
}
