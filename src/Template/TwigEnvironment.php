<?php

namespace Drupal\loft_dev\Template;

use Twig\Template;

class TwigEnvironment extends \Drupal\Core\Template\TwigEnvironment {

  /**
   * @var null|string
   */
  private $templateFilepath;

  /**
   * Override this method to add the filepath to the template.
   *
   * The filepath is used by the file_header() function provided by this module.
   *
   * @param string $name
   * @param null $index
   *
   * @return mixed|\Twig_TemplateInterface
   * @throws \Twig\Error\RuntimeError
   */
  public function loadTemplate(string $cls, string $name, int $index = NULL): Template {
    if (file_exists($name)) {
      $this->templateFilepath = file_exists($name) ? $name : NULL;
    }

    return parent::loadTemplate($cls, $name, $index);
  }

  /**
   * Get the filepath to the last template loaded.
   *
   * @return string|null
   *   If not available, this will return null.
   */
  public function getTemplateFilepath() {
    return $this->templateFilepath;
  }
}
