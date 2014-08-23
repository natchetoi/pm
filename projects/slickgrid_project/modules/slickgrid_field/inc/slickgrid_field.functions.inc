<?php

/*
 * @return list of nodetypes with name and type
 */
function slickgrid_field_get_node_fields($content_type) {
  $options = array('target' => 'slave');



  $sql = "SELECT fc.field_name,fc.type
          FROM field_config_instance fci inner join field_config fc on fci.field_name=fc.field_name 
          WHERE fci.bundle = :content_type ";

  $result = db_query($sql, array(':content_type' => $content_type,), $options);
  $fields = array();
  $fields[] = array('name' => 'title', 'type' => 'text');
  foreach ($result->fetchAll() as $key => $field) {
    $fields[] = array('name' => $field->field_name, 'type' => $field->type);
  }

  return $fields;
}