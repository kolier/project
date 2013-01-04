<?php

/**
 * @file
 * Project pages.
 */

/**
 * Menu title callback.
 */
function project_page_title(Project $project) {
  return $project->label();
}

/**
 * Menu page callback.
 */
function project_page_view(Project $project) {
  return $project->view();
}
