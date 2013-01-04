<?php

/**
 * @file
 * Entity metadata.
 */

/**
 * Implements hook_entity_property_info().
 */
function project_entity_property_info() {
  $info = array();
  $properties = &$info['project']['properties'];
  
  $properties['type'] = array(
    'label' => t("Type"),
    'type' => 'project_type',
    'description' => t("The project type."),
    'schema field' => 'type',
  );
  $properties['title'] = array(
    'label' => t("Title"),
    'type' => 'text',
    'description' => t("The title of this project."),
    'schema field' => 'title',
  );
  $properties['name'] = array(
    'label' => t("Name"),
    'type' => 'text',
    'description' => t("The machine_name of this project."),
    'schema field' => 'name',
  );
  $properties['uid'] = array(
    'label' => t("Author"),
    'type' => 'user',
    'description' => t("The creator of this project."),
    'schema field' => 'uid',
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
  
  $properties = &$info['project_type']['properties'];
  
  $properties['type'] = array(
    'label' => t("Type"),
    'type' => 'text',
    'description' => t("The project type machine_name."),
    'schema field' => 'type',
  );
  $properties['label'] = array(
    'label' => t("Label"),
    'type' => 'text',
    'description' => t("The label of this project type."),
    'schema field' => 'label',
  );
  
  return $info;
}
