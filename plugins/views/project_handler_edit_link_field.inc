<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */


class project_handler_edit_link_field extends project_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy project to check access against
    $dummy_project = (object) array('type' => $type);
    if (!project_access('edit', $dummy_project)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $project_id = $values->{$this->aliases['project_id']};
    
    return l($text, 'admin/content/projects/project/' . $project_id . '/edit');
  }
}
