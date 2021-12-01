<?php

namespace Drupal\loft_dev;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\DependencyInjection\ServiceProviderBase;
use Drupal\loft_dev\Template\TwigEnvironment;

/**
 * Extends core's TwigEnvironment with filename context.
 *
 * @// TODO I wonder if this should be decorated instead per https://symfony.com/doc/current/service_container/service_decoration.html?
 */
class LoftDevServiceProvider extends ServiceProviderBase {

  /**
   * {@inheritdoc}
   */
  public function alter(ContainerBuilder $container) {
    if ($container->hasDefinition('twig')) {
      $definition = $container->getDefinition('twig');
      $definition->setClass(TwigEnvironment::class);
    }
  }
}
