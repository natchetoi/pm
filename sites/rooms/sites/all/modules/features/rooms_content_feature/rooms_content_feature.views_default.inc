<?php
/**
 * @file
 * rooms_content_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function rooms_content_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'units';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'rooms_units';
  $view->human_name = 'Units';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Units';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Bookable Units: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'rooms_units';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Bookable Units: Base_price */
  $handler->display->display_options['fields']['base_price']['id'] = 'base_price';
  $handler->display->display_options['fields']['base_price']['table'] = 'rooms_units';
  $handler->display->display_options['fields']['base_price']['field'] = 'base_price';
  $handler->display->display_options['fields']['base_price']['precision'] = '0';
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* Field: Bookable Units: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['label'] = '';
  $handler->display->display_options['fields']['field_description']['element_label_colon'] = FALSE;
  /* Field: Field: Options */
  $handler->display->display_options['fields']['rooms_booking_unit_options']['id'] = 'rooms_booking_unit_options';
  $handler->display->display_options['fields']['rooms_booking_unit_options']['table'] = 'field_data_rooms_booking_unit_options';
  $handler->display->display_options['fields']['rooms_booking_unit_options']['field'] = 'rooms_booking_unit_options';
  $handler->display->display_options['fields']['rooms_booking_unit_options']['delta_offset'] = '0';
  /* Filter criterion: Bookable Units: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'rooms_units';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'standart_doubles' => 'standart_doubles',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'units';
  $export['units'] = $view;

  return $export;
}
