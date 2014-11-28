<?php
/**
 * @file
 * Admin forms for configurations
 */



// Always includes common file.
module_load_include('inc', 'gearman_integration', 'inc/gearman_integration.common');
module_load_include('php', 'gearman_integration', 'inc/GearmanTelnet');


/**
 * Implements function to show admin configuration form().
 */
function gearman_integration_admin_general_settings() {
  $form = array();

  $form['gearman_integration'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['gearman_integration']['gearman_server_url'] = array(
    '#type'          => 'textfield',
    '#size'          => 40,
    '#title'         => t('Gearman Server URL/IP'),
    '#default_value' => variable_get('gearman_server_url', GEARMAN_DEFAULT_SERVER),
    '#description'   => t('The server you want to connect to.'),
    '#required'      => TRUE,
  );

  $form['gearman_integration']['gearman_server_port'] = array(
    '#type'          => 'textfield',
    '#size'          => 40,
    '#title'         => t('Gearman Server`s Port'),
    '#default_value' => variable_get('gearman_server_port', GEARMAN_DEFAULT_PORT),
    '#description'   => t('The server`s port to be used.'),
    '#required'      => TRUE,
  );

  $form['gearman_integration_server_information'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Gearman Server Information'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  if (variable_get('gearman_server_url') && variable_get('gearman_server_port')) {

    $form['gearman_integration_server_information']['jobs'] = array(
    '#markup' => _gearman_integration_get_server_jobs(),
    '#prefix' => '<h2>Registered Jobs</h2>',
    
    );

    $form['gearman_integration_server_information']['workers'] = array(
    '#markup' => _gearman_integration_get_server_workers(),
    '#prefix' => '<h2>Registered Workers</h2>',
    
    );

   // $form['gearman_integration_server_information']['Connected Clientes'] = array(
   //  '#markup' => _gearman_integration_get_server_conected_clients(),
   //  '#prefix' => '<h2>Registered Clients</h2>',
    
    // );

  }
  
  

   $form['#validate'][] = 'gearman_settings_validate';



  return system_settings_form($form);
}

function gearman_settings_validate($form, $form_state) {
  //Get Server Params
  $server = variable_get('gearman_server_url');
  $port = variable_get('gearman_server_port');
  
  //create our Gearman Server
  if (!empty($server) && !empty($port)) {
    if ($gearmanHost = GearmanHost::singleton($server, $port)) {
      drupal_set_message(t('The Gearman server is responding properly.'));
    }
    else {
      form_set_error('gearman_server', t('The Gearman server could no be reached!'));
    }
  }
 }