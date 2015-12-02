<?php

$keys1  = ['a', 'b'];
$keys2  = ['c', 'd'];
$array1 = ['a' => 'alpha', 'b' => 'beta', 'c' => 'capa'];
$array2 = ['b' => 'beta', 'c' => 'capa', 'd' => 'delta'];
var_dump(
  rs_array_keys_exist($keys1, $array1),
  rs_array_keys_exist($keys2, $array1),
  rs_array_keys_exist($keys1, $array2),
  rs_array_keys_exist($keys2, $array2)
);
// throws exception
var_dump(
  rs_array_keys_exist()
);
die();
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('rs')) {
	dl('rs.' . PHP_SHLIB_SUFFIX);
}
$module = 'rs';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";
?>
