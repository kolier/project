<?php

/**
 * @file
 * Entity metadata
 */

/**
 * Implements hook_entity_property_info().
 */
function project_entity_property_info() {
  $info = array();
  $properties = &$info['project']['properties'];
  
  $properties['type'] = array(
    'label' => t("Project type"),
    'type' => 'text',
    'description' => t("The project type."),
    'schema field' => 'type',
  );
  $properties['name'] = array(
    'label' => t("Project name"),
    'type' => 'text',
    'description' => t("The machine_name of this project."),
    'schema field' => 'name',
  );
  $properties['title'] = array(
    'label' => t("Project title"),
    'type' => 'text',
    'description' => t("The title of this project."),
    'schema field' => 'title',
  );
  $properties['created'] = array(
    'label' => t("Date created"),
    'type' => 'date',
    'description' => t("The date the project was created."),
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t("Date changed"),
    'type' => 'date',
    'schema field' => 'changed',
    'description' => t("The date the project was most recently updated."),
  );
  
  return $info;
}
