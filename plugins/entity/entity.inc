<?php

/**
 * @file
 * Store the main Entity class.
 */

/**
 * The class used for project entities
 */
class Project extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'project');
  }

  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => $this->entityInfo['admin ui']['path'] . '/' . $this->project_id);
  }
  
  public function editUri() {
    return array('path' => $this->entityInfo['admin ui']['path'] . '/' . $this->project_id . '/edit');
  }
  
  public function deleteUri() {
    return array('path' => $this->entityInfo['admin ui']['path'] . '/' . $this->project_id . '/delete');
  }
  
  public function adminUri() {
    return array('path' => $this->entityInfo['admin ui']['path']);
  }
}

/**
 * The class used for project type entities
 */
class ProjectType extends Entity {

  public $type;
  public $label;

  public function __construct($values = array()) {
    parent::__construct($values, 'project_type');
  }
}
