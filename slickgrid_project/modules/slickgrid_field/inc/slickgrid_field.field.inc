<?php
/**
 * @file
 * Slickgrid file info
 */
/**
 * Implements hook_field_info().
 *
 * Provides the description of the field.
 */
function slickgrid_field_field_info() {
  return array(
    // We name our field as the associative name of the array.
    'slickgrid_field' => array(
      'label' => t('Slickgrid table'),
      'description' => t('Demonstrates a field composed of an RGB color.'),
      'default_widget' => 'slickgrid_field_default_widget',
      'default_formatter' => 'slickgrid_field_default_formatter',
    ),
  );
}

/**
 * Implements hook_field_validate().
 *
 * This hook gives us a chance to validate content that's in our
 * field. We're really only interested in the $items parameter, since
 * it holds arrays representing content in the field we've defined.
 * We want to verify that the items only contain RGB hex values like
 * this: #RRGGBB. If the item validates, we do nothing. If it doesn't
 * validate, we add our own error notification to the $errors parameter.
 *
 * @see slickgrid_field_field_widget_error()
 */
function slickgrid_field_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  /*
    foreach ($items as $delta => $item) {
    if (!empty($item['slickgrid'])) {
    if (! preg_match('@^#[0-9a-f]{6}$@', $item['slickgrid'])) {
    $errors[$field['field_name']][$langcode][$delta][] = array(
    'error' => 'slickgrid_field_invalid',
    'message' => t('Color must be in the HTML format #abcdef.'),
    );
    }
    }
    }
   */
}

/**
 * Implements hook_field_is_empty().
 *
 * hook_field_is_emtpy() is where Drupal asks us if this field is empty.
 * Return TRUE if it does not contain data, FALSE if it does. This lets
 * the form API flag an error when required fields are empty.
 */
function slickgrid_field_field_is_empty($item, $field) {
  drupal_set_message('field is empty');
  return empty($item['slickgrid']);
}
/**
 * Implements hook_field_settings_form().
 */
function slickgrid_field_field_settings_form($field, $instance, $has_data) {
  $form = array();
  $form['export'] = array(
    '#type' => 'checkbox',
    '#title' => 'Allow users to export table data as CSV',
    '#default_value' => isset($field['settings']['export']) ? $field['settings']['export'] : FALSE,
  );
  $form['lock_values'] = array(
    '#type' => 'checkbox',
    '#title' => 'Lock table field defaults from further edits during node add/edit.',
    '#default_value' => isset($field['settings']['lock_values']) ? $field['settings']['lock_values'] : FALSE,
  );

  $form['default_message'] = array(
    '#type' => 'markup',
    '#value' => t('To specify a default table, use the &quot;Default Value&quot; above. There you can specify a default number of rows/columns and values.'),
  );

  return $form;
}