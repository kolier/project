<?php

/**
 * @file
 * Entity UI controller.
 */

class ProjectUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    // admin/content/projects and admin/content/projects/list are views.

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a project',
      'description' => 'Add a new project',
      'page callback'  => 'project_admin_add',
      'access callback'  => 'project_access',
      'access arguments' => array('edit'),
      'file' => 'project.admin.inc',
      'file path' => drupal_get_path('module', 'project'),
      // Why admin/commerce/products can show? 'type' => MENU_NORMAL_ITEM | MENU_LOCAL_ACTION,
      'weight' => 10,
    );

    // Add menu items to add each different type of entity.
    foreach (project_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add !type',
        'title arguments' => array('!type' => $type->label),
        'page callback' => 'project_edit_form_wrapper',
        'page arguments' => array(project_create(array('type' => $type->type))),
        'access callback' => 'project_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'project.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module']),
      );
    }

    // Menu item for project view/edit/delete.
    $items[$this->path . '/' . $wildcard] = array(
      'title callback' => 'project_page_title',
      'title arguments' => array(1),
      'page callback' => 'project_page_view',
      'page arguments' => array(1),
      'access callback' => 'project_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
      'file' => 'project.pages.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    $items[$this->path . '/' . $wildcard] = array(
      'page callback' => 'project_edit_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'project_access',
      'access arguments' => array('edit', $id_count),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'project_delete_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'project_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );

    return $items;
  }
}

class ProjectTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage project types, including fields.';

    return $items;
  }
}
