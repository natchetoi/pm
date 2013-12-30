<?php
/**
 * @file 
 * slickgrid field widget file
 */

/**
 * Implements hook_field_widget_info().
 *
 * Three widgets are provided.
 * - A simple text-only widget where the user enters the '#ffffff'.
 * - A 3-textfield widget that gathers the red, green, and blue values
 *   separately.
 * - A farbtastic colorpicker widget that chooses the value graphically.
 *
 * These widget types will eventually show up in hook_field_widget_form,
 * where we will have to flesh them out.
 *
 * @see slickgrid_field_field_widget_form()
 */
function slickgrid_field_field_widget_info() {
  return array(
    'slickgrid_field_default_widget' => array(
      'label' => t('Slickgrid default widget'),
      'field types' => array('slickgrid_field'),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 *
 * hook_widget_form() is where Drupal tells us to create form elements for
 * our field's widget.
 *
 * We provide one of three different forms, depending on the widget type of
 * the Form API item provided.
 *
 * The 'slickgrid_field_colorpicker' and 'slickgrid_field_text' are essentially
 * the same, but slickgrid_field_colorpicker adds a javascript colorpicker
 * helper.
 *
 * slickgrid_default_widget displays three text fields, one each for red, green,
 * and blue. However, the field type defines a single text column,
 * rgb, which needs an HTML color spec. Define an element validate
 * handler that converts our r, g, and b fields into a simulated single
 * 'slickgrid' form element.
 */
function slickgrid_field_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
 
// Because we have many fields with the same values, we have to set
  // #tree to be able to access them.
  $form['#tree'] = TRUE;
  
  
  $value = isset($items[$delta]['slickgrid']) ? $items[$delta]['slickgrid'] : '';
  $widget = $element;
  $widget['#delta'] = $delta;
  $widget['#tree'] = TRUE;
//dsm($value);
//dsm($field['settings']);
  //dsm($instance['widget']['type']);
  $id = drupal_html_id(implode('-', array('slickgrid_field', $element['#field_name'], $element['#delta'], 'edit')));

  switch ($instance['widget']['type']) {
    case 'slickgrid_field_default_widget':
    default: 
$widget['slickgrid'] = array(
        '#type' => 'fieldset',
        '#title' => t('Slickgrid'),
        '#prefix'=>'<div class="slickgrid_edit_wrapper">',
        '#suffix'=>'</div>',
      );
        
      $selected = isset($form_state['values']['op']) ? $form_state['values']['op'] : t('Structure');
if($selected==t('View')){
$widget['slickgrid']['table_view'] = array(
        '#type' => 'slickgrid',
        '#left_value' => 0,
        '#right_value' => 200,
        '#left' => t('Left text'),
        '#right' => t('Right text'),
        '#size' => 4,
      );
 
  $widget['slickgrid']['change_view'] = array(
    '#type' => 'submit',
    '#prefix'=>t('Change view to:'),
    '#ajax' => array(
      'callback' => 'slickgrid_field_change_view_callback',
      'wrapper' => 'slickgrid_edit_wrapper',
    ),
    '#value' => t('Structure'),
  );
  

}else{
  
  
  
  $widget['slickgrid']['description'] = array(
    '#markup' => '<div>' . t('This example shows an add-more and a remove-last button. The <a href="!ajax">AJAX version</a> does it without page reloads; the <a href="!multistep">non-js version</a> is the same code but simulates a non-javascript environment, showing it with page reloads.',
      array('!ajax' => url('examples/ajax_example/add_more'), '!multistep' => url('examples/ajax_example/add_more_no_js')))
    . '</div>',
  );

 
  $widget['slickgrid']['names_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('People coming to the picnic'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="names-fieldset-wrapper">Test',
    '#suffix' => '</div>',
  );

  // Build the fieldset with the proper number of names. We'll use
  // $form_state['num_names'] to determine the number of textfields to build.
  if (empty($form_state['num_names'])) {
    $form_state['num_names'] = 1;
  }
  for ($i = 0; $i < $form_state['num_names']; $i++) {
    $widget['slickgrid']['names_fieldset']['name'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
    );
  }
 $widget['slickgrid']['names_fieldset']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('slickgrid_field_change_view_add_more_add_one'),
    // See the examples in ajax_example.module for more details on the
    // properties of #ajax.
    '#ajax' => array(
      'callback' => 'slickgrid_field_change_view_add_more_callback',
      'wrapper' => 'names-fieldset-wrapper',
    ),
  );
  if ($form_state['num_names'] > 1) {
    $widget['slickgrid']['names_fieldset']['remove_name'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('slickgrid_field_change_view_add_more_remove_one'),
      '#ajax' => array(
        'callback' => 'slickgrid_field_change_view_add_more_callback',
        'wrapper' => 'names-fieldset-wrapper',
      ),
    );
  }
 

  // This simply allows us to demonstrate no-javascript use without
  // actually turning off javascript in the browser. Removing the #ajax
  // element turns off AJAX behaviors on that element and as a result
  // ajax.js doesn't get loaded.
  // For demonstration only! You don't need this.
  /*if ($no_js_use) {
    // Remove the #ajax from the above, so ajax.js won't be loaded.
    if (!empty($widget['slickgrid']['names_fieldset']['remove_name']['#ajax'])) {
      unset($widget['slickgrid']['names_fieldset']['remove_name']['#ajax']);
    }
    unset($widget['slickgrid']['names_fieldset']['add_name']['#ajax']);
  }*/
    $widget['slickgrid']['change_view'] = array(
    '#type' => 'submit',
    '#prefix'=>t('Change view to:'),
    '#ajax' => array(
      'callback' => 'slickgrid_field_change_view_callback',
      'wrapper' => 'slickgrid_edit_wrapper',
    ),
    '#value' => t('View'),
  );

}/*
  drupal_set_message($form_state['values']['op']);
 $widget['slickgrid']['values'] = array(
    //'#type'=>'value'
   '#markup' =>  $form_state['values']['op'],
 );
   */
/*
      $widget['create_slickgrid'] = array(
        '#type' => 'fieldset',
        '#title' => t('Creating a new formatter'),
      );

      $full_types = node_type_get_types();

      $node_types = array();
      foreach ($full_types as $key => $val) {
        $node_types[$key] = $val->name;
      }

      //$fields = slickgrid_field_get_node_fields('slickgrid');      
      //drupal_set_message("<pre>".print_r($fields,true)."</pre>");



      $widget['create_slickgrid']['create_slickgrid_format_type'] = array(
        '#type' => 'radios',
        '#options' => array(t('From exist slickgrid format'), t('From exist content type'), t('With the help of wizard')),
        '#title' => t('Please select format type'),
        '#default_value' => $value,
      );

      $widget['create_slickgrid']['create_slickgrid_node_type'] = array(
        '#type' => 'select',
        '#options' => $node_types,
        '#title' => t('Please select the node type'),
        '#default_value' => $value,
      );   $widget['create_slickgrid']['table_fields'] = array(
        '#type' => 'markup',
        '#prefix' => '<div id="test-form-wrapper">',
        '#suffix' => '</div>',
        '#markup' => "",
      );

       $widget['slickgrid_header'] = array(
        '#type' => 'hidden',
        '#title' => t('Type'),
        '#default_value' => $value['type'],
        '#attributes' => array('class' => array('slickgrid-field-header-' . $id)),
      );

       $widget['slickgrid_table'] = array(
        '#type' => 'hidden',
        '#title' => t('Type'),
        '#default_value' => $value['type'],
        '#attributes' => array('class' => array('slickgrid-field-table-' . $id)),
      );

       $widget['slickgrid_options'] = array(
        '#type' => 'hidden',
        '#title' => t('Type'),
        '#default_value' => $value['type'],
        '#attributes' => array('class' => array('slickgrid-field-options-' . $id)),
      );
*//*
      $widget['create_slickgrid']['create_slickgrid_format'] = array(
        '#type' => 'submit',
        '#value' => 'test',
        '#title' => 'test',
        '#default_value' => $value,
        '#ajax' => array(
          'callback' => 'slickgrid_field_create_slickgrid_format',
          'wrapper' => 'test-form-wrapper',
        ),
      );
*/


      break;
  }

  $element['slickgrid'] = $widget;
  //drupal_set_message("<pre>".print_r($widget,true)."</pre");
  return $element;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function  slickgrid_field_change_view_add_more_callback($form, &$form_state) {
  return $form['slickrid'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function slickgrid_field_change_view_add_more_add_one($form, &$form_state) {
  $form_state['num_names']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function slickgrid_field_change_view_add_more_remove_one($form, &$form_state) {
  if ($form_state['num_names'] > 1) {
    $form_state['num_names']--;
  }
  $form_state['rebuild'] = TRUE;
}
function slickgrid_field_change_view_callback($form,&$form_state){
 // drupal_set_message('change view');
 //drupal_set_message('<pre>'.print_r($form_state['values']['op'],true).'</pre>');
   drupal_set_message('<pre>'.print_r($form['slickgrid'],true).'</pre>');
  $widget['slickgrid']['values'] = array(
    //'#type'=>'value'
   '#markup' =>  $form_state['values']['op'],
 );
  //return $widget;
  return $form['slickgrid'];
}
/**
 * Implements hook_field_widget_error().
 *
 * hook_field_widget_error() lets us figure out what to do with errors
 * we might have generated in hook_field_validate(). Generally, we'll just
 * call form_error().
 *
 * @see slickgrid_field_field_validate()
 * @see form_error()
 */
function slickgrid_field_field_widget_error($element, $error, $form, &$form_state) {
  switch ($error['error']) {
    case 'slickgrid_field_invalid':
      form_error($element, $error['message']);
      break;
  }
}

/**
 * Validate the individual fields and then convert them into a single HTML RGB
 * value as text.
 */
function slickgrid_default_widget_validate($element, &$form_state) {
  $delta = $element['#delta']; // TODO: Isn't there a better way to find out which element?
  $field = $form_state['field'][$element['#field_name']][$element['#language']]['field'];
  $field_name = $field['field_name'];
  drupal_set_message('validate');
  if (isset($form_state['values'][$field_name][$element['#language']][$delta]['slickgrid'])) {

    $values = $form_state['values'][$field_name][$element['#language']][$delta]['slickgrid'];
    $value = $values['test'];
    form_set_value($element, $value, $form_state);
  }
}