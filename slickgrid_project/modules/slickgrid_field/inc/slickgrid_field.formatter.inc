<?php
/**
 * @file
 * formatter field
 */

/**
 * Implements hook_field_formatter_info().
 *
 * We need to tell Drupal that we have two different types of formatters
 * for this field. One will change the text color, and the other will
 * change the background color.
 *
 * @see slickgrid_field_field_formatter_view()
 */
function slickgrid_field_field_formatter_info() {
  return array(
    // This formatter just displays the hex value in the color indicated.
    'slickgrid_default_formatter' => array(
      'label' => t('Simple text-based formatter'),
      'field types' => array('slickgrid_field'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 *
 * Two formatters are implemented.
 * - slickgrid_default_formatter just outputs markup indicating the color that
 *   was entered and uses an inline style to set the text color to that value.
 * - slickgrid_field_color_background does the same but also changes the
 *   background color of div.region-content.
 *
 * @see slickgrid_field_field_formatter_info()
 */
function slickgrid_field_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {
    // This formatter simply outputs the field as text and with a color.
    case 'slickgrid_default_formatter':
      foreach ($items as $delta => $item) {

        /*
          $element[$delta] = array(
          // We create a render array to produce the desired markup,
          // "<p style="color: #hexcolor">The color code ... #hexcolor</p>".
          // See theme_html_tag().
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#attributes' => array(
          'style' => 'color: ' . $item['slickgrid'],
          ),
          '#value' => t('The color code in this field is @code', array('@code' => $item['slickgrid'])),
          );
         */
        //drupal_set_message($item['slickgrid']);
        drupal_set_message('field');
        drupal_set_message($field);
        $path = drupal_get_path('module', 'slickgrid_field');
        drupal_add_js(array('slickgrid_field' => array('id' => "myGrid_default_formatter")), 'setting');

        $element[$delta] = array(
          '#type' => 'markup',
          '#markup' => "
			<div class='myGrid_default_formatter_wrapper' style='width:600px;'>
					<div id='myGrid_default_formatter' style='width:100%;height:200px;'></div>

			<div id='slickgrid-value' class='slickgrid-value' value='" . $item['slickgrid'] . "'></div>
			</div>
			",
          '#attached' => array(
            // Add javascript to trigger the colorpicker.
            'js' => array(
              $path . '/js/lib/firebugx.js',
              $path . '/js/lib/jquery-1.7.min.js',
              $path . '/js/lib/jquery-ui-1.8.16.custom.min.js',
              $path . '/js/lib/jquery.event.drag-2.2.js',
              $path . '/js/slick.core.js',
              //$path . '/js/plugins/slick.cellrangedecorator.js',
              //$path . '/js/plugins/slick.cellrangeselector.js',
              //$path . '/js/plugins/slick.cellselectionmodel.js',
              $path . '/js/slick.formatters.js',
              $path . '/js/slick.editors.js',
              $path . '/js/plugins/slick.rowselectionmodel.js',
              $path . '/js/slick.grid.js',
              $path . '/js/slick.dataview.js',
              $path . '/controls/slick.pager.js',
              $path . '/controls/slick.columnpicker.js',
              $path . '/js/slickgrid_field_default_formatter.js',
            ),
            'css' => array(
              $path . '/css/slick-default-theme.css',
              $path . '/css/slick.grid.css',
              $path . '/css/jquery-ui-1.8.16.custom.css',
              $path . '/css/slickgrid_field.css',
            ),
          ),
        );
      }
      break;

  }

  return $element;
}
