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
	
	
	//$form['reset']['#value'] = l(t('Reset'), 'media/photos');
	
	
	$var_get = variable_get('shared_permission_types', array());
	
	$form['shared_permission_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content-type for Node Publish Tools'),
    '#default_value' => $var_get,
    '#options' => $reference_types,
    '#description' => t('Content type to be used for the node publish tools'),
  );
	
	return system_settings_form($form);
}