<?php

/**
 * @file
 * The controller for the project entity containing the CRUD operations.
 */

/*
// A revision version.
class ProjectEntityController extends DrupalDefaultEntityController implements EntityAPIControllerInterface {
	
}
*/

/**
 * The Controller for Project entities
 */
class ProjectController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Create a model - we first set up the values that are specific
   * to our model schema but then also go through the EntityAPIController
   * function.
   *
   * @param $type
   *   The machine-readable type of the model.
   *
   * @return
   *   A model object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Project
    $values += array(
      'project_id' => '',
      'is_new' => TRUE,
      'title' => '',
      'uid' => NULL,
      'created' => '',
      'changed' => '',
      'data' => '',
    );

    $project = parent::create($values);
    return $project;
  }
}

/**
 * The Controller for Project Type entities
 */
class ProjectTypeController extends EntityAPIControllerExportable {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Create a model type - we first set up the values that are specific
   * to our model type schema but then also go through the EntityAPIController
   * function.
   *
   * @param $type
   *   The machine-readable type of the model.
   *
   * @return
   *   A model type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our project_type
    $values += array(
      'id' => '',
      'is_new' => TRUE,
      'data' => '',
      'status' => '',
    );
    
    $project_type = parent::create($values);
    return $project_type;
  }
}
