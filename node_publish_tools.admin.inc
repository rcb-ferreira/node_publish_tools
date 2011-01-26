<?php
// $Id$

/**
 * @file
 * Administrative page callbacks for the Node Publish Tools module.
 *
 * @ingroup Node Publish Tools
 */
 
/**
 * Implementations of profile wizard settings form
 */ 
function node_publish_tools_settings_form() {
  $form = array();
  // get all content types
	$types = array();
  foreach (node_get_types('types') as  $type) {
    $types[$type->type] = $type->name;
  }
	// get all types that has user reference fields
	$reference_types = array();
	foreach ($types as $key => $type) {
		$fields = array();
		$type_info = content_types($key);
		foreach($type_info['fields'] as $field) {
			if ($field['type'] == 'userreference')
				$reference_types[$key] = $type;
		}
	}
	// user reference types
	if (count($reference_types) > 0)
	$form['shared_permission_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content-type for Shared User reference'),
    '#default_value' => variable_get('shared_permission_types', null),
    '#options' => $reference_types,
    '#description' => t('Content type to be used for the node publish tools'),
  );
	
	// publish tools types
	$form['node_publish_tools_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content-type for Node Publish Tools'),
    '#default_value' => variable_get('node_publish_tools_types', null),
    '#options' => $types,
    '#description' => t('Content types to add node publish functionality to.'),
  );
	return system_settings_form($form);
}


/**
 * Theme function for node_publish_tools popups.
 */
function node_publish_tools_preprocess_node_publish_tools(&$vars) {
  if (!empty($vars['links']) && is_array($vars['links'])) {
    $links = '';
    foreach ($vars['links'] as $link) {
      $links .= l($link['title'], $link['href'], $link);
    }
    $vars['links'] = $links;
  }
}