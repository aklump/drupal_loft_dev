<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInit4bdd7b1528b870bea1beec02a8692852
{
    public static $prefixLengthsPsr4 = array (
        'S' => 
        array (
            'Symfony\\Component\\Yaml\\' => 23,
        ),
        'D' => 
        array (
            'Drupal\\loft_dev\\' => 16,
        ),
        'A' => 
        array (
            'AKlump\\LoftLib\\' => 15,
        ),
    );

    public static $prefixDirsPsr4 = array (
        'Symfony\\Component\\Yaml\\' => 
        array (
            0 => __DIR__ . '/..' . '/symfony/yaml',
        ),
        'Drupal\\loft_dev\\' => 
        array (
            0 => __DIR__ . '/../..' . '/src/Drupal/loft_dev',
        ),
        'AKlump\\LoftLib\\' => 
        array (
            0 => __DIR__ . '/../..' . '/lib/loft_php_lib/dist/src/AKlump/LoftLib',
        ),
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixLengthsPsr4 = ComposerStaticInit4bdd7b1528b870bea1beec02a8692852::$prefixLengthsPsr4;
            $loader->prefixDirsPsr4 = ComposerStaticInit4bdd7b1528b870bea1beec02a8692852::$prefixDirsPsr4;

        }, null, ClassLoader::class);
    }
}