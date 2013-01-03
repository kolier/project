<?php

/**
 * @file
 * Implements Views API.
 */

/**
 * Implements hook_views_data_alter()
 */
function project_views_data_alter(&$data) {
  $data['project']['link_project'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the project.'),
      'handler' => 'project_handler_link_field',
    ),
  );
  $data['project']['edit_project'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the project.'),
      'handler' => 'project_handler_edit_link_field',
    ),
  );
  $data['project']['delete_project'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the project.'),
      'handler' => 'project_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows project/%project_id/op
  $data['project']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this project.'),
      'handler' => 'project_handler_project_operations_field',
    ),
  );
}
