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
  $types = array(0 => 'none');
  foreach (node_get_types('types') as  $type) {
    $types[$type->type] = $type->name;
  }
  $form['node_publish_tools_type'] = array(
    '#type' => 'select',
    '#title' => t('Content-type for Node Publish Tools'),
    '#default_value' => variable_get('node_publish_tools_type', null),
    '#options' => $types,
    '#description' => t('Content type to be used for the node publish tools'),
  );
  
	// if no other type selected return basic form
  if (variable_get('node_publish_tools_type', null) == null)
		return system_settings_form($form);
		
	// get all type fields
	$fields = array();
  $type_info = content_types(variable_get('node_publish_tools_type', null));
  foreach($type_info['fields'] as $field) {
    $fields[$field['field_name']] = $field['widget']['label'];
		}
	
  
	if (sizeof($fields) > 0)
	$form['node_publish_tools_steps'] = array(
    '#type' => 'select',
    '#title' => t('Amount of steps needed'),
    '#default_value' => variable_get('node_publish_tools_steps', null),
    '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
    '#description' => t('Amount of steps to be used for wizard'),
  );
	
  if (sizeof($fields) > 0 && variable_get('node_publish_tools_steps', null) == 1) {
		$form['node_publish_tools_fields'] = array(
			'#type' => 'checkboxes',
			'#title' => t('Fields to use'),
			'#default_value' => variable_get('profilewizard_fields', null),
			'#options' => $fields,
			'#description' => t('Fields to use for the profile wizard'),
		);
		} 
	}
  return system_settings_form($form);
}