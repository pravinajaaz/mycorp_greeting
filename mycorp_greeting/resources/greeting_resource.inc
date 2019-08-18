<?php

/**
 * @file
 *  Provides callback functions for Greeting resources
 */

/**
 * Returns the results of a node_load() for the specified greeting.
 *
 *
 * @param $nid
 *   NID of the greeting we want to return.
 * @return
 *   Greeting object or service error if not found.
 *
 */
function _greeting_resource_retrieve($nid) {
  if(_greeting_check_greeting_nid($nid)) {
    $node = node_load($nid);
    return $node;
  }
  else{
    return services_error(t('The greeting id is not found'), 404);
  }
}

/**
 * Creates a new greeting based on submitted values.
 *
 * @param $node
 *   Array representing the attributes a node.
 * @return
 *   nid of the created greeting.
 */
function _greeting_resource_create($node) {
  global $user;
  $greeting = new stdClass();
  if(isset($node['title']) && $node['title']!='' ){
    $greeting->title = $node['title'];
    $greeting->type = "greeting";
    node_object_prepare($greeting);
    $greeting->language = LANGUAGE_NONE;
    $greeting->uid = $user->uid;
    $greeting->status = 1;
    $greeting->promote = 0;
    if(isset($node['field_greeting_image'])){
      $url=$node['field_greeting_image'];
      $file_temp = file_get_contents($url);
      $public_url="public://".basename($url);
      $file_temp = file_save_data($file_temp, $public_url, FILE_EXISTS_RENAME);
      $greeting->field_greeting_image = array(
        'und' => array(
          0 => array(
            'fid' => $file_temp->fid,
            'filename' => $file_temp->filename,
            'filemime' => $file_temp->filemime,
            'uid' => 1,
            'uri' => $file_temp->uri,
            'status' => 1,
            'display' => 1
          )
        )
      );
    }
    $greeting = node_submit($greeting); // Prepare node for saving
    node_save($greeting);
    $greeting_id = $greeting->nid;
    if($greeting_id>0){
      return $greeting_id;
    }
    else{
      return services_error(t('The greeting is not created'));
    }
  }
  else{
    return services_error(t('Greeting title is required.'));
  }

}


/**
 * Updates a greeting based on submitted values.
 *
 * @param $nid
 *   Node ID of the node we're editing.
 * @param $node
 *   Array representing the attributes a node.
 * @return
 *   The greeting object that has been updated.
 *
 */
function _greeting_resource_update($nid, $node) {
  if(_greeting_check_greeting_nid($nid)){
    $greeting = node_load($nid);
    if(isset($node['field_greeting_image'])){
      $url=$node['field_greeting_image'];
      $file_temp = file_get_contents($url);
      $public_url="public://".basename($url);
      if (!$file_temp = file_save_data($file_temp, $public_url, FILE_EXISTS_RENAME)) {
      return services_error(t('Failed to upload file. @upload', array('@upload' => $key)), 406);
      }
      if ($file_temp->fid) {
        $greeting->field_greeting_image = array(
          'und' => array(
            0 => array(
              'fid' => $file_temp->fid,
              'filename' => $file_temp->filename,
              'filemime' => $file_temp->filemime,
              'uid' => 1,
              'uri' => $file_temp->uri,
              'status' => 1,
              'display' => 1
            )
          )
        );
      }
    }
    if(isset($node['title'])){
      $greeting->title = $node['title'];
    }
    node_save($greeting);
    return $greeting;
  }
  else{
    return services_error(t('The greeting id is not found'), 404);
  }
}

/**
 * Delete a greeting given its nid.
 *
 * @param int $nid
 *   Node ID of the greeting we're deleting.
 * @return bool
 *   Returns true.
 */
function _greeting_resource_delete($nid) {
  if(_greeting_check_greeting_nid($nid)) {
       node_delete($nid);
      return TRUE;
  } else {
    return services_error(t('The greeting id is not found'), 404);
  }
  return $output;
}

/**
 * Provides the list of greeting items.
 *
 * @return
 *   Returns associative array of greeting title.
 */
function _greeting_resource_index() {
 $nids = db_select('node', 'n')
              ->fields('n', array('nid'))
              ->condition('n.type', 'greeting')
              ->execute()
              ->fetchCol();
  $output = [];
  foreach ($nids as $nid) {
    $node = node_load($nid);
    $output[$nid]=$node->title;
  }
  if(empty($output)) {
    return services_error(t('The greeting list is empty'));
  } else {
    return $output;
  }
}

/**
 * Determine whether the current user can access a greeting resource.
 *
 * @param $op
 *   One of view, update, create, delete per node_access().
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 *
 */
function _greeting_resource_access($op = 'view', $args = array()) {
  // Make sure we have an object or this all fails, some servers can
  // mess up the types.
  if (is_array($args[0])) {
    $args[0] = (object) $args[0];
  }
  elseif (!is_array($args[0]) && !is_object($args[0])) {  //This is to determine if it is just a string happens on node/%NID
    $args[0] = (object)array('nid' => $args[0]);
  }

  if ($op != 'create' && !empty($args)) {
    $node = node_load($args[0]->nid);
  }
  elseif ($op == 'create') {
    return node_access($op, 'greeting');
  }
  if (isset($node->nid) && $node->nid) {
    return node_access($op, $node);
  }
  else {
    return services_error(t('Greeting @nid could not be found', array('@nid' => $args[0]->nid)), 404);
  }
}

/**
 * Publish/unpublish a greeting given its nid.
 *
 * @param int $nid
 *   Node ID of the greeting we publish/unpublish.
 * @return bool
 *   Returns true.
 */
function _greeting_resource_publish($nid){
  if(_greeting_check_greeting_nid($nid)){
    $node = node_load($nid);
    $node->status = !$node->status;
    node_save($node);
    return TRUE;
  }
  else{
    return services_error(t('The greeting id is not found'), 404);
  }
  return $output;
}

/**
 * Check if the nid belongs to greeting type.
 *
 * @param int $nid
 *   Node ID of the greeting we're checking.
 * @return bool
 *   Returns true or false.
 */
function _greeting_check_greeting_nid($nid) {
  $greeting_id = db_select('node', 'n')
              ->fields('n', array('nid'))
              ->condition('n.type', 'greeting')
              ->condition('n.nid', $nid)
              ->execute()->fetchCol();
  if(count($greeting_id) > 0) {
    return TRUE;
  }
  return FALSE;
}
