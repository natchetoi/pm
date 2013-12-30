<?php
/*
* @file
*/
/*
 * implements hook_theme().
 */
function slickgrid_field_theme(){
  $items['slickgrid_field'] = array(
    'variables' => array(),
  );
  $items['slickgrid_element'] = array(
    'render element' => 'element',
    'variables'      => array(),
  );
  
   return $items;
}

function theme_slickgrid_element($variables) {
  //return '<h1>test slickgrid theme</h1>';
}
/**
 * The main theme function for the slickgrid
 * @param array $view_name
 */

function theme_slickgrid_field($variables) {
  $view = $variables['view'];
  // Add all the CSS & JS
  // Add the core slickgrid library
  drupal_add_library('slickgrid', 'slickgrid');
  // Add this modules slickgrid files
  $path = drupal_get_path('module', 'slickgrid');
  // Add bespoke slickgrid js/css
  drupal_add_js($path . '/js/slickgrid.js');
  drupal_add_js($path . '/js/slickgrid.theme.js');
  drupal_add_css($path . '/css/slickgrid.css');
  // Add beautytips
  beautytips_add_beautytips();
  // If this slickgrid is editable, add the ctools modal plugins
  if (isset($view->style_plugin->options['editable']) || isset($view->style_plugin->options['add'])) {
    slickgrid_add_modal();
  }
  // Inline JS defining the slickgrid
  $js = array();
  $js[] = 'var options = ' . drupal_json_encode($view->style_plugin->options) . ';';
  $js[] = 'var data = [];';
  
  if (count($view->data)) {
    $js[] = 'data = ' . drupal_json_encode($view->data) . ';';
  }
  
  $js[] = 'var columns = ' . slickgrid_encode_columns($view->columns) . ';';
  $js[] = 'var slickgrid;';
  $js[] = '(function($) {';
  $js[] = '$(document).ready(function(){';
  $js[] = 'slickgrid = new Slickgrid("#slickgrid", "' . $view->name . '", "' . $view->current_display . '", "' . url(SLICKGRID_CALLBACK_PATH) . '");';
  $js[] = '});';
  $js[] = '})(jQuery);';
  
  drupal_add_js(implode("\n", $js), array(
    'type' => 'inline'
  ));
  
  $output = '<div id="slickgrid" style="width:100%;height:' . $view->style_plugin->options['viewport_height'] . 'px;" class="hideCols hideRows' . (isset($view->style_plugin->options['editable']) && $view->style_plugin->options['editable'] ? ' editable' : '') . '"></div>';
  
  return $output;
}


function slickgrid_field_element_info() {
  $types['slickgrid'] =  array(
    '#input'            => TRUE,
    '#process'          => array('slickgrid_field_element_process'),
    '#element_validate' => array('slickgrid_field_element_validate'),
    '#left'             => t('Left'),
    '#right'            => t('Right'),
    '#header'           => t('header'),
    '#options'          => t('Options'),
    '#theme'            => array('slickgrid_element'),
    '#left_value'       => 0,
    '#right_value'      => 100,
    '#header_value'     => array(),
    '#options_value'    => array(),
    '#size'             => 5,
  );
  return $types;
  
}
function slickgrid_field_element_validate($element, &$form_state) {
  // Здесь надо проверить, что сумма, введённая при создании элемента формы равна той,
  // которую мы получили при сабмите формы
  //$sum = $element['#left_value'] + $element['#right_value'];
  //if (($element['#value']['left'] + $element['#value']['right']) != $sum) {
//    form_error($element, t("The sum of left and right values doesn't check with original."));
  //}
}
function slickgrid_field_element_process($element) {
 
  // Делаем элемент деревом, чтобы он в себе хранил значения дочерних элементов
  $element['#tree'] = TRUE;
 
  // Для слайдера нам потребуется 2 поля ввода - левое и правое значение слайдера.
  // Из формы, которая будет создана разработчикам, создаём новые элементы с 
  // использованием уже известных элементов Forms API
 
  // Создаём левое поле ввода
  $element['left'] = array(
    '#type'             => 'textfield',
    '#field_prefix'     => $element['#left'],
    '#default_value'    => $element['#left_value'],
    //'#element_validate' => array('jslider_form_api_validate_integer'),
    '#size'             => $element['#size'],
  );
 
  // Создаём правое поле ввода
  $element['right'] = array(
    '#type'             => 'textfield',
    '#field_suffix'     => $element['#right'],
    '#default_value'    => $element['#right_value'],
    //'#element_validate' => array('jslider_form_api_validate_integer'),
    '#size'             => $element['#size'],
  );
 
  
  
      $columns = array(
        array('id' => "sel", 'name' => "#", 'field' => "num", 'behavior' => "select", 'cssClass' => "cell-selection", 'width' => 40, 'cannotTriggerInsert' => true, 'resizable' => false, 'selectable' => false),
        array('id' => "title", 'name' => "Title", 'field' => "title", 'width' => 120, 'minWidth' => 120, 'cssClass' => "cell-title", 'editor' => 'Slick.Editors.Text', 'validator' => 'requiredFieldValidator', 'sortable' => true),
        array('id' => "duration", 'name' => "Duration", 'field' => "duration", 'editor' => 'Slick.Editors.Text', 'sortable' => true),
        array('id' => "%", 'defaultSortAsc' => false, 'name' => "% Complete", 'field' => "percentComplete", 'width' => 80, 'resizable' => false, 'formatter' => 'Slick.Formatters.PercentCompleteBar', 'editor' => 'Slick.Editors.PercentComplete', 'sortable' => true),
        array('id' => "start", 'name' => "Start", 'field' => "start", 'minWidth' => 60, 'editor' => 'Slick.Editors.Date', 'sortable' => true),
        array('id' => "finish", 'name' => "Finish", 'field' => "finish", 'minWidth' => 60, 'editor' => 'Slick.Editors.Date', 'sortable' => true),
        array('id' => "effort-driven", 'name' => "Effort Driven", 'width' => 80, 'minWidth' => 20, 'maxWidth' => 80, 'cssClass' => "cell-effort-driven", 'field' => "effortDriven", 'formatter' => 'Slick.Formatters.Checkmark', 'editor' => 'Slick.Editors.Checkbox', 'cannotTriggerInsert' => true, 'sortable' => true)
      );

      $options = array();
      $data = array();

    //  dsm($element);

      $slickgrid_obj = array(
        'id' => $element['#id'].'_table',
        'columns' => $columns,
        'data' => $data,
        'options' => $options,
      );

      drupal_add_js(array('slickgrid_field' => array('id' => $slickgrid_obj['id'], 'slickgrid_obj' => $slickgrid_obj)), 'setting');
      $path = drupal_get_path('module', 'slickgrid_field');

      $widget['test'] = array(
        '#type' => 'textarea',
        '#suffix' => '<div style="width:600px;">
					<div id="' . $slickgrid_obj['id'] . '" style="width:100%;height:200px;"></div>
			</div>',
        '#title' => 'test',
        '#default_value' => $element['#value'],
      
      );

      // Map container.
      $element['slickgrid_table_container'] = array(
        '#markup' => '<div id="' . $slickgrid_obj['id'] . '" style="width:100%;height:400px"></div>',
          '#attached' => array(
          // Add Farbtastic color picker.
          'library' => array(
            array('system', 'farbtastic'),
          ),
          // Add javascript to trigger the colorpicker.
          'js' => array(
            $path . '/js/lib/firebugx.js',
            $path . '/js/lib/jquery-1.7.min.js',
            $path . '/js/lib/jquery-ui-1.8.16.custom.min.js',
            $path . '/js/lib/jquery.event.drag-2.2.js',
            $path . '/js/slick.core.js',
            $path . '/js/slick.formatters.js',
            $path . '/js/slick.editors.js',
            $path . '/js/plugins/slick.rowselectionmodel.js',
            $path . '/js/slick.grid.js',
            $path . '/js/slick.dataview.js',
            $path . '/controls/slick.pager.js',
            $path . '/controls/slick.columnpicker.js',
            $path . '/js/slickgrid_field.js',
          ),
          'css' => array(
            $path . '/css/slick-default-theme.css',
            $path . '/css/slick.grid.css',
            $path . '/css/jquery-ui-1.8.16.custom.css',
            $path . '/css/slickgrid_field.css',
          ),
        ),
      );
  // Возвращаем обновлённый элемент
  return $element;
}