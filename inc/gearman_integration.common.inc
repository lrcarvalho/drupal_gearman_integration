<?php
/**
 * @file
 * Gearman menu common functions.
 */

// Always includes common file.
 module_load_include('inc', 'gearman_integration', 'inc/gearman_classes');
 module_load_include('php', 'gearman_integration', 'inc/GearmanTelnet');

 //$abla = new GearmanTelnet();

 //$abla2 = new GearmanHost();
 //exit(var_dump($abla2));


function _gearman_integration_get_server_workers() {
    $gearmanServer = GearmanHost::singleton(variable_get('gearman_server_url'),variable_get('gearman_server_port'));
    $workers = $gearmanServer->getWorkers();
    $markup = '';
    if (!is_null($workers)) {
        
        foreach ($workers as $worker => $detail) {
            $markup .= '<ul>';
            $markup .= '<li><b>Worker: </b>' . $worker . '</li>';
            $markup .= '<li> <b>Available:</b> ' . $detail['AVAILABLE'] . '</li>';
            $markup .= '<li> <b>Total:</b> ' . $detail['TOTAL'] . '</li>';
            $markup .= '<li> <b>Running:</b> ' . $detail['RUNNING'] . '</li>';
            $markup .= '<li> <b>Queued:</b> ' . $detail['QUEUED'] . '</li>';
            $markup .= '</ul><br>';
           
        }
        ;
    }
    
  return $markup;
}


function _gearman_integration_get_server_jobs() {
    $gearmanServer = GearmanHost::singleton(variable_get('gearman_server_url'),variable_get('gearman_server_port'));
    $jobs = $gearmanServer->getJobs();
    $markup = '';
    if (!is_null($jobs)) {
        
        foreach ($jobs as $job => $detail) {
            $markup .= '<ul>';
            $markup .= '<li><b>Job Name: </b>' . $job . '</li>';
            $markup .= '<li> <b>Available:</b> ' . $detail['AVAILABLE'] . '</li>';
            $markup .= '<li> <b>Total:</b> ' . $detail['TOTAL'] . '</li>';
            $markup .= '<li> <b>Running:</b> ' . $detail['RUNNING'] . '</li>';
            $markup .= '</ul><br>';
           
        }
        ;
    }
    
  return $markup;
}

function _gearman_integration_get_server_conected_clients() {
    $gearmanServer = new Waps_Gearman_Server();
    $status = $gearmanServer->getStatus();
    $markup = '';
    if (!is_null($status['connections'])) {
        $markup = '';
     
        foreach ($status['connections'] as $key => $connection) {
            $markup .= '<br><ul>';
            $markup .= '<li> <b>Client ID:</b> ' . $key . '</b></li>';
            $markup .= '<li> <b>Fd:</b> ' . $connection['fd'] . '</li>';
            $markup .= '<li> <b>Ip:</b> ' . $connection['ip'] . '</li>';
            $markup .= '<li> <b>Id:</b> ' . $connection['id'] . '</li>';
            $markup .= '<li> <b>Function being executed:</b> ' . $connection['function'] . '</li>';        
            $markup .= '</ul><br>';
        }
        
    }
    
  return $markup;
}