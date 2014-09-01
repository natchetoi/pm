<?php

/**
 * @file
 * Handles the form elements of the customer survey form
 * All hooks are in the .module file.
 */

/**
 * Master form which calls an individual form for each step.
 * 
 * @see customer_survey_form_validate().
 * @see customer_survey_form_submit().
 * 
 * @param type $form
 * @param string $form_state
 * @return type 
 */
function customer_survey_form($form, &$form_state) {

  drupal_add_css(drupal_get_path('module', 'customer_survey') . '/css/customer_survey.css');

  if (!isset($form_state['stage'])) $form_state['stage'] = 'rate_the_room';
 
  $form = array();
  $form = customer_survey_get_header($form, $form_state);

  switch ($form_state['stage']) {
    
    case 'rate_the_room':
      return customer_survey_rate_the_room_form($form, $form_state);
     break;  
 
    case 'rate_the_service': 
      return customer_survey_rate_the_service_form($form, $form_state);  
     break;
 
    case 'personal_details': 
      return customer_survey_personal_details_form($form, $form_state);  
     break;
 
    default:
      return customer_survey_rate_the_room_form($form, $form_state);
     break; 
  }
  
  return $form;
    
}


/**
 * Form for the rate_the_room step.
 * 
 * @see customer_survey_form().
 *  
 * @param type $form
 * @param type $form_state
 * @return type 
 */
function customer_survey_rate_the_room_form($form, &$form_state) {
    
  $values = isset($form_state['multistep_values']['rate_the_room']) ? $form_state['multistep_values']['rate_the_room'] : array();

  $form['rate_the_room']['room_rating'] = array(
    '#type' => 'radios',
    '#title' => 'How would you rate the room you stayed in?',
    '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
    '#default_value' => isset($values['room_rating']) ? $values['room_rating'] : NULL,
  );
  
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next')
  );
    
  return $form;
}


/**
 * Form for the rate_the_service step.
 * 
 * @see customer_survey_form().
 *  
 * @param type $form
 * @param type $form_state
 * @return type 
 */
function customer_survey_rate_the_service_form($form, &$form_state) {
    
  $values = isset($form_state['multistep_values']['rate_the_service']) ? $form_state['multistep_values']['rate_the_service'] : array();

  $form['rate_the_service']['service_rating'] = array(
    '#type' => 'radios',
    '#title' => 'How would you rate our service?',
    '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
    '#default_value' => isset($values['service_rating']) ? $values['service_rating'] : NULL,
  );
  
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Back')
  );
  
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next')
  );
    
  return $form;
}


/**
 * Form for the personal_details step.
 * 
 * @see customer_survey_form().
 *  
 * @param type $form
 * @param type $form_state
 * @return type 
 */
function customer_survey_personal_details_form($form, &$form_state) {

  $values = isset($form_state['multistep_values']['personal_details']) ? $form_state['multistep_values']['personal_details'] : array();

  $form['personal_details']['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#default_value' => isset($values['name']) ? $values['name'] : NULL,
  );
  
  $form['personal_details']['email'] = array(
    '#type' => 'textfield',
    '#title' => 'Email',
    '#default_value' => isset($values['email']) ? $values['email'] : NULL,
  );
 
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Back')
  );
  
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  
  return $form;
}

function i2i_eco_payment_wizard_form_step_4($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'customer_survey') . '/css/customer_survey.css');
  if (!isset($form_state['stage'])) $form_state['stage'] = 'step_5_1';
dsm($form_state);
  $form = array();
  $form = i2i_eco_payment_wizard_form_step_4_navigation($form, $form_state);

  switch ($form_state['stage']) {

    case 'step_5_1':
      return i2i_eco_payment_wizard_form_step_4_1($form, $form_state);
      break;

    case 'step_5_2':
      return i2i_eco_payment_wizard_form_step_4_2($form, $form_state);
      break;

    case 'step_5_3':
      return i2i_eco_payment_wizard_form_step_4_3($form, $form_state);
      break;

    default:
      return customer_survey_rate_the_room_form($form, $form_state);
      break;
  }

  return $form;
}

function i2i_eco_payment_wizard_form_step_4_submit($form, &$form_state) {

  switch ($form_state['stage']) {

    case 'step_5_3':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      if ($form_state['triggering_element']['#value'] != 'Back') {
        i2i_eco_payment_wizard_form_step_4_personal_details_submit($form, $form_state);
        $form_state['complete'] = TRUE;
      }
      break;

    default:
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      $form_state['new_stage'] = i2i_eco_payment_wizard_form_step_4_move_to_next_stage($form, $form_state);
      break;

  }

  if (isset($form_state['complete'])) drupal_goto('complete-page');

  if ($form_state['triggering_element']['#value'] == 'Back') {
    $form_state['new_stage'] = customer_survey_move_to_previous_stage($form, $form_state);
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['stage'] = $form_state['new_stage'];
  $form_state['rebuild'] = TRUE;

}
function i2i_eco_payment_wizard_form_step_4_move_to_next_stage($form, &$form_state) {

  switch ($form_state['stage']) {
    case 'step_5_1':
      return 'step_5_2';
      break;

    case 'step_5_2':
      return 'step_5_3';
      break;
  }

}

function i2i_eco_payment_wizard_form_step_4_personal_details_submit($form, &$form_state) {

  $multstep_values = $form_state['multistep_values'];

  $module = 'customer_survey';
  $key = 'customer_survey_complete';

  $to = $multstep_values['personal_details']['email'] . '; ' . variable_get('site_mail', 'admin@example.com');
  $from = variable_get('site_mail', 'admin@example.com');

  $params = array(
    'body' => 'Thank you for filling in our survey. You have now been entered into our prize draw.',
    'subject' => 'Thank you for filling in our survey, ' . $multstep_values['personal_details']['name'],
  );

  $language = language_default();
  $send = TRUE;
  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }

}
function i2i_eco_payment_wizard_form_step_4_navigation($form, &$form_state) {

  $form_state['stage'] = isset($form_state['stage']) ? $form_state['stage'] : 1;

  $form_stages = array(
    'step_5_1' => 1,
    'step_5_2' => 2,
    'step_5_3' => 3,
  );

  if (isset($form_stages[$form_state['stage']])) {
    $current_step = $form_stages[$form_state['stage']];
  }
  else {
    $current_step = 1;
  }

  $stages = array(
    1 => array('data' => '1. Step 1'),
    2 => array('data' => '2. Step 2'),
    3 => array('data' => '3. Step 3'),
  );
  $stages[$current_step]['class'] = array('active');
  $stages_list = theme('item_list', array('items' => $stages));
  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#value' => $stages_list,
  );

  return $form;

}
function i2i_eco_payment_wizard_form_step_4_1($form, &$form_state){
  $values = isset($form_state['multistep_values']['step_5_1']) ? $form_state['multistep_values']['step_5_1'] : array();

  $form['step_5_1']['markup'] = array(
    '#markup' => 'step 1',
  );
  $form['step_5_1']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'title',
    '#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  $form['step_5_1']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('first name'),
    '#default_value' => isset($values['first_name']) ? $values['first_name'] : NULL,
  );
  $form['step_5_1']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($values['last_name']) ? $values['last_name'] : NULL,
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Save and next')
  );
  return $form;
}
function i2i_eco_payment_wizard_form_step_4_2($form, &$form_state){
  $form['step_5_2']['markup'] = array(
    '#markup' => 'step 2',
  );
  $form['step_5_2']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'title',
    '#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  $form['step_5_2']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('first name'),
    '#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  $form['step_5_2']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($values['last_name']) ? $values['last_name'] : NULL,
  );
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Save and next')
  );
  return $form;
}
function i2i_eco_payment_wizard_form_step_4_3($form, &$form_state){
  $form['step_5_3']['markup'] = array(
    '#markup' => 'step 3',
  );
  $form['step_5_3']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'title',
    '#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  $form['step_5_3']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('first name'),
    '#default_value' => isset($values['title']) ? $values['title'] : NULL,
  );
  $form['step_5_3']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($values['last_name']) ? $values['last_name'] : NULL,
  );
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Save and next')
  );
  return $form;
}