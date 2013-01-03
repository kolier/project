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
    
    /*
    $items[$this->path] = array(
      'title' => 'Projects',
      'description' => 'Manage projects.',
      'type' => MENU_LOCAL_TASK | MENU_NORMAL_ITEM,
      'page callback' => 'project_overview_page',
      'access arguments' => array('access administration pages'),
      'file' => 'project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    
    // Overview.
    // @todo access control.
    $item[$this->path . '/list'] = array(
      'title' => 'Manage projects',
      'description' => 'Manage project entities.',
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );
    */   
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
        'page callback' => 'project_form_wrapper',
        'page arguments' => array(project_create(array('type' => $type->type))),
        'access callback' => 'project_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'project.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module']),
      );
    }
  
    // Loading and editing project entities
    $items[$this->path . '/' . $wildcard] = array(
      'page callback' => 'project_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'project_access',
      'access arguments' => array('edit', $id_count),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
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
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
  
    // Menu item for viewing projects
    $items['project/' . $wildcard] = array(
      'title callback' => 'project_page_title',
      'title arguments' => array(1),
      'page callback' => 'project_page_view',
      'page arguments' => array(1),
      'access callback' => 'project_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    
    return $items;
  }
  
  /**
   * Create the markup for the add Model Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);
  
    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }
  
    return theme('project_add_list', array('content' => $content));
  }
}

function project_form($form, &$form_state, $project, $op = 'edit') {
  $form['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => $project->title,
    '#required' => TRUE,
    '#size' => 30,
  );
  
  dsm($project);
  
  field_attach_form('project', $project, $form, $form_state);
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save project'),
    '#weight' => 40,
  );
  
  return $form;
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
