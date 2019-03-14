<?php

namespace Drupal\loft_dev\Service;

use Drupal\Core\Config\ConfigFactoryInterface;

/**
 * Core functionality provided by the loft_dev module.
 */
class LoftDev {

  /**
   * An instance of the config factory.
   *
   * @var \Drupal\Core\Config\ConfigFactoryInterface
   */
  protected $configFactory;

  /**
   * The settings for this module.
   *
   * @var \Drupal\Core\Config\ImmutableConfig
   */
  protected $settings;

  /**
   * LoftDev constructor.
   *
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   An instance of ConfigFactory.
   */
  public function __construct(ConfigFactoryInterface $config_factory) {
    $this->configFactory = $config_factory;
    $this->settings = $this->configFactory->get('loft_dev.settings');
  }

  /**
   * Return the properly configured email address for reroute_email.
   *
   * @return string|false
   *   The email address if reroute_email module is properly configured.
   */
  public function getProperlyConfiguredRerouteEmailAddress() {
    global $config;

    $settings = $config['reroute_email.settings'] ?? [];
    if (!empty($settings['address']) && !empty($settings['enable'])) {
      return $settings['address'];
    }
    return FALSE;
  }

}
