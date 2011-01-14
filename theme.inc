<?php

/**
 * Theme function for contextual popups.
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
