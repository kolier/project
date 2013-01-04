<?php

/**
 * @file
 * Project admin.
 */

/**
 * Menu callback: display a list of product types that the user can create.
 */
function project_admin_add() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the admin/commerce/products/add listing if only one product type is
  // available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }

  return theme('project_add_list', array('content' => $content));
}

/**
 * Displays the list of available project types for model creation.
 *
 * @ingroup themeable
 */
function theme_project_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="project-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer project types')) {
      $output = '<p>' . t('Project Entities cannot be added because you have not created any project types yet. Go to the <a href="@create-project-type">project type creation page</a> to add a new project type.', array('@create-project-type' => url('admin/structure/project-types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No project types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * A wrapper for the project_edit_form to pass project entity object.
 * 
 * @param Project $project
 */
function project_edit_form_wrapper(Project $project) {
  return drupal_get_form('project_edit_form', $project);
}

/**
 * Form for add/edit a project.
 */
function project_edit_form($form, $form_state, Project $project) {
  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Project Name'),
    '#default_value' => isset($project->title) ? $project->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  // Machine-readable name of the project.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($project->name) ? $project->name : '',
    '#maxlength' => 255,
    '#disabled' => !empty($project->title),
    '#machine_name' => array(
      'exists' => 'project_exists',
      'source' => array('title'),
    ),
    '#description' => t('A unique machine-readable name for this project. It must only contain lowercase letters, numbers, and underscores.'),
  );
  
  // Add the field related form elements.
  $form_state['project'] = $project;
  field_attach_form('project', $project, $form, $form_state);
  
  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );
  
  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();
  
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save project'),
    '#submit' => $submit + array('project_edit_form_submit'),
  );
  
  if (!empty($project->title)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete project'),
      '#suffix' => l(t('Cancel'), 'admin/project/projects'),
      '#submit' => $submit + array('project_edit_form_submit_delete'),
      '#weight' => 45,
    );
  }
  
  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  //$form['#validate'][] = 'model_edit_form_validate';

  return $form;
}

/**
 * Submit of project_edit_form.
 */
function project_edit_form_submit(&$form, &$form_state) {
  global $user;

  $project = entity_ui_controller('project')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  if ($project->is_new = isset($project->is_new) ? $project->is_new : 0){
    $project->created = time();
    $project->uid = $user->uid;
  }
  $project->changed = time();
  $project->save();
  $admin_uri = $project->adminUri();
  $form_state['redirect'] = $admin_uri['path'];
}

/**
 * Submit of project_edit_form for delete.
 */
function project_edit_form_submit_delete(&$form, &$form_state) {
  $project = entity_ui_controller('project')->entityFormSubmitBuildEntity($form, $form_state);
  $delete_uri = $project->deleteUri();
  $form_state['redirect'] = $delete_uri['path'];
}

function project_delete_form_wrapper(Project $project) {
  return drupal_get_form('project_delete_form', $project);
}

/**
 * Form callback: confirmation form for deleting a project.
 *
 * @param $project
 *   The project object to be deleted.
 *
 * @see confirm_form()
 */
function project_delete_form($form, &$form_state, Project $project) {
  $form_state['project'] = $project;

  $form['#submit'][] = 'project_delete_form_submit';

  $content = entity_view('project', array($project->project_id => $project));

  $form = confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $project->title)),
    '',
    drupal_render($content) . '<p>' . t('Deleting this product cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for project_project_delete_form().
 */
function project_delete_form_submit($form, &$form_state) {
  $project = $form_state['project'];

  if (project_delete($project->project_id)) {
    drupal_set_message(t('%title (Name: @name) has been deleted.', array('%title' => $project->title, '@name' => $project->name)));
    watchdog('project', 'Deleted product %title (Name: @name).', array('%title' => $project->title, '@name' => $project->name), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('%title could not be deleted.', array('%title' => $project->title)), 'error');
  }
  
  $admin_uri = $project->adminUri();
  $form_state['redirect'] = $admin_uri['path'];
}

function project_type_form($form, &$form_state, $project_type, $op = 'edit') {
  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $project_type->label,
    '#description' => t('The human-readable name of this project type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($project_type->type) ? $project_type->type : '',
    '#maxlength' => 32,
    //'#disabled' => $project_type->isLocked() && $op != 'clone',
    '#disabled' => FALSE,
    '#machine_name' => array(
      'exists' => 'project_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this project type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save project type'),
    '#weight' => 40,
  );

  return $form;
}

function project_type_form_submit(&$form, &$form_state) {
  $project_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $project_type->save();
  $form_state['redirect'] = 'admin/project/projects/types';
}

function project_type_form_submit_delete(&$form, &$form_state) {
}
