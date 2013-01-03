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
    return array('path' => 'project/' . $this->project_id);
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
