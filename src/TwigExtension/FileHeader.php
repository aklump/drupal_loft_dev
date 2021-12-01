<?php

namespace Drupal\loft_dev\TwigExtension;

use Drupal\Core\Render\Markup;
use \Drupal\Core\Template\TwigEnvironment;
use Twig\Extension\AbstractExtension;
use Twig\TwigFunction;

/**
 * This will not work if your template starts uses {% extends "block.html.twig"
 * %}, int that case try commenting out the extends line and run this to
 * generate the header, then uncomment.
 *
 * @see \Drupal\loft_dev\Template\TwigEnvironment.
 */
class FileHeader extends AbstractExtension {

  /**
   * Prevents processing the same file more than once by tracking an index.
   *
   * @var array
   */
  private $processed = [];

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return 'file_header.twig_extension';
  }

  /**
   * {@inheritdoc}
   */
  public function getFunctions() {
    return [
      new TwigFunction('file_header', function (TwigEnvironment $env, $context) {

        $path_to_template_file = $env->getTemplateFilepath();
        if (!$path_to_template_file) {
          \Drupal::messenger()
            ->addWarning(Markup::create("The <code>file_header()</code> function is not available when twig caching is enabled.  Disable the twig cache using <em>development.services.yml</em> and reload your twig file to write the file header. Add the following and rebuild cache: <pre><code>parameters:
  twig.config:
    debug: true
    auto_reload: true
    cache: false</code></pre>"));
        }

        // Prevent processing more than once.
        elseif (!in_array($path_to_template_file, $this->processed)) {
          static::getFileHeader($path_to_template_file, $context);
          $this->processed[] = $path_to_template_file;
        }
      }, [
        'needs_context' => TRUE,
        'needs_environment' => TRUE,
      ]),
    ];
  }

  /**
   * Generate Twig template file stub.
   *
   * Place the following at the top of an empty twig file and load the page.
   * The content should change and you should see a file header in it's place.
   *
   * The name of the file must be {anything}.html.twig
   *
   * @code
   * {{ file_header() }}
   * @endcode
   *
   * @param       $template_file
   * @param array $vars
   *
   * @throws \InvalidArgumentException If the filename is misnamed.
   * @throws \RuntimeException If the file cannot be written.
   */
  public static function getFileHeader($template_file, array $vars) {
    $template_file = preg_replace('/\.php$/', '', $template_file);
    if (!preg_match('/\.html\.twig$/', $template_file)) {
      throw new \InvalidArgumentException("Filename must end in .html.twig");
    }

    // Filter out camel case, duplicated vars.
    $vars = array_diff_key($vars, array_flip(array_filter(array_keys($vars), function ($key) use ($vars) {
      return $key !== strtolower($key);
    })));

    // Filter out other vars by key.
    unset($vars['twig']);

    $stub = _loft_dev_file_header(__FUNCTION__, $template_file, $vars, FALSE);
    $stub = str_replace("<?php\n", '', $stub);
    $stub = "{#\n" . trim($stub) . PHP_EOL . '#}';

    $contents = file_get_contents($template_file);
    $contents = preg_replace('/^\s*{{ file_header\(\) }}\s*/', '', $contents);
    $stub .= PHP_EOL . PHP_EOL . ltrim($contents);

    if (!file_put_contents($template_file, $stub)) {
      throw new \RuntimeException("Could not write file.");
    }
  }

}
