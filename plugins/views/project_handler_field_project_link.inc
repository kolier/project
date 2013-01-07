<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying links to entities
 * as fields.
 */

class project_handler_field_project_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['project_id'] = 'project_id';
    $this->additional_fields['type'] = 'type';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => 'View', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $project_id = $values->{$this->aliases['project_id']};
    $text = !empty($this->options['text']) ? $this->options['text'] : url('admin/project/projects/' . $project_id, array('absolute' => TRUE));

    return l($text, 'admin/project/projects/' . $project_id);
  }
}
