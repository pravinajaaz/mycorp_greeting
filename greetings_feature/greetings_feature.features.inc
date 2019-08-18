<?php

/**
 * @file
 * greetings_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function greetings_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_node_info().
 */
function greetings_feature_node_info() {
  $items = array(
    'greeting' => array(
      'name' => t('Greeting'),
      'base' => 'node_content',
      'description' => t('Allows you to create greeting that will be used in services'),
      'has_title' => '1',
      'title_label' => t('Greeting Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
