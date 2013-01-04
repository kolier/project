<?php

/**
 * This field handler aggregates operations that can be done on a project
 * under a single field providing a more flexible way to present them in a view
 */
class project_handler_field_project_link_operations extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['project_id'] = 'project_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('project', 'admin/project/projects', array($this->get_value($values, 'project_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
