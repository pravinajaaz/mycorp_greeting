<?php

/**
 * @file
 * greetings_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function greetings_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-greeting-field_greeting_image'.
  $field_instances['node-greeting-field_greeting_image'] = array(
    'bundle' => 'greeting',
    'deleted' => 0,
    'description' => 'Image related to the greeting',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_greeting_image',
    'label' => 'Greeting Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => -3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Greeting Image');
  t('Image related to the greeting');

  return $field_instances;
}
