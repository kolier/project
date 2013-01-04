<?php

/**
 * @file
 * Implements Views API.
 */

/**
 * Implements hook_views_data_alter()
 */
function project_views_data_alter(&$data) {
  // Links.
  $data['project']['link'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the project.'),
      'handler' => 'project_handler_field_project_link',
    ),
  );
  $data['project']['link_edit'] = array(
    'field' => array(
      'title' => t('Link edit'),
      'help' => t('Provide a link to the edit form for the project.'),
      'handler' => 'project_handler_field_project_link_edit',
    ),
  );
  $data['project']['link_delete'] = array(
    'field' => array(
      'title' => t('Link delete'),
      'help' => t('Provide a link to delete the project.'),
      'handler' => 'project_handler_field_project_link_delete',
    ),
  );
  $data['project']['link_operations'] = array(
    'field' => array(
      'title' => t('Links operations'),
      'help' => t('Display all operations available for this project.'),
      'handler' => 'project_handler_field_project_link_operations',
    ),
  );
  
  $data['project']['empty_text'] = array(
    'title' => t('Empty text'),
    'help' => t('Displays an appropriate empty text message for project lists.'),
    'area' => array(
      'handler' => 'project_handler_area_project_empty_text',
    ),
  );
}
