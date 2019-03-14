<?php

namespace Drupal\loft_dev\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * @Block (
 *   id = "loft_dev_tools",
 *   admin_label = @Translation("Loft Dev Tools"),
 *   category = @Translation("Development"),
 * )
 */
class LoftDevTools extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {

    if (!_loft_dev_access()) {
      return [];
    }
    $loft_dev = \Drupal::service('loft_dev');

    $build = [];
    $build['#attached']['library'][] = 'system/collapse';

    // The links for example pages.
    $links = [];
    $links['theme'] = [
      'title' => 'Elements',
      'url' => 'loft-dev/theme',
    ];
    $links['access-denied'] = [
      'title' => '403',
      'url' => 'loft-dev/theme/403',
    ];
    $links['not-found'] = [
      'title' => '404',
      'url' => 'loft-dev/theme/404',
    ];
    $links['maintenance'] = [
      'title' => 'Offline',
      'url' => 'loft-dev/theme/offline',
    ];
    $links['playground'] = [
      'title' => 'Theme Playground',
      'url' => 'loft-dev/theme/playground',
    ];
    $links['teasers'] = [
      'title' => 'Teasers',
      'url' => 'loft-dev/theme/teasers',
    ];
    $links['font-sizing'] = [
      'title' => t('Font Size'),
      'url' => 'admin/loft-dev/rem',
      'attributes' => [
        'onclick' => 'window.open(this.href, "REM Sizing", "status=0,toolbar=0,location=0,menubar=0,directories=0,resizable=1,scrollbars=0,height=650,width=120"); return false;',
      ],
    ];
    $build['theming-pages'] = [
      '#theme' => 'links',
      '#links' => $links,
      '#heading' => [
        'text' => 'Theming Pages',
        'level' => 'h2',
        'class' => [],
      ],
      '#attributes' => [
        'class' => ['links', 'inline'],
      ],
    ];

    // Node suite.
    $links = [];
    foreach (loft_dev_node_suite() as $type => $nid) {
      $links['node-' . $type] = [
        'title' => $type,
        'url' => 'node/' . $nid,
      ];
    }
    $build['node_suite'] = [
      '#theme' => 'links',
      '#links' => $links,
      '#heading' => [
        'text' => 'Node Suite',
        'level' => 'h2',
        'class' => [],
      ],
      '#attributes' => [
        'class' => ['links', 'inline'],
      ],
    ];

    // Links from other modules.
    $links = \Drupal::moduleHandler()->invokeAll('loft_dev_menu');
    $build['loft_menu'] = [
      '#theme' => 'links',
      '#links' => $links,
      '#heading' => [
        'text' => 'Loft Menu',
        'level' => 'h2',
        'class' => [],
      ],
      '#attributes' => [
        'class' => ['links', 'inline'],
      ],
    ];

    $output = '';
    $output .= \Drupal::service("renderer")->render($build);
    $output = str_replace('href="/%23"', 'href="#"', $output);

    if (0) {
      $form = \Drupal::formBuilder()->getForm('loft_dev_node_access_form');
      $output .= \Drupal::service("renderer")->render($form) . "\n";
    }

    if (\Drupal::moduleHandler()->moduleExists('masquerade') &&
      ($temp = \Drupal::moduleHandler()
        ->invoke('masquerade', 'block_view', [0]))
    ) {
      if (is_string($temp['content'])) {
        $temp['content'] = ['#markup' => $temp['content']];
      }
      $output .= '<h3>' . $temp['subject'] . '</h3>' . "\n";
      $output .= \Drupal::service("renderer")
          ->render($temp['content']) . "\n";
    }

    // @FIXME
    // menu_tree() is gone in Drupal 8. To generate or work with menu trees, you'll need to
    // use the menu.link_tree service.
    //
    //
    // @see https://www.drupal.org/node/2226481
    // @see https://api.drupal.org/api/drupal/core%21lib%21Drupal%21Core%21Menu%21MenuLinkTree.php/class/MenuLinkTree/8
    // $tree = menu_tree('devel');

    $output .= render($tree);

    if (($temp = \Drupal::moduleHandler()
      ->invoke('devel_node_access', 'block_view', [0]))) {
      if (is_string($temp['content'])) {
        $temp['content'] = ['#markup' => $temp['content']];
      }
      $output .= '<h3>' . $temp['subject'] . '</h3>' . "\n";
      $output .= \Drupal::service("renderer")
          ->render($temp['content']) . "\n";
    }

    if (($temp = \Drupal::moduleHandler()
      ->invoke('devel_node_access', 'block_view', [1]))) {
      if (is_string($temp['content'])) {
        $temp['content'] = ['#markup' => $temp['content']];
      }
      $output .= '<h3>' . $temp['subject'] . '</h3>' . "\n";
      $output .= \Drupal::service("renderer")
          ->render($temp['content']) . "\n";
    }

    if (\Drupal::moduleHandler()
        ->moduleExists('func_search') && ($temp = \Drupal::moduleHandler()
        ->invoke('func_search', 'block_view', [0]))) {
      if (is_string($temp['content'])) {
        $temp['content'] = ['#markup' => $temp['content']];
      }
      $output .= '<h3>' . $temp['subject'] . '</h3>' . "\n";
      $output .= \Drupal::service("renderer")
          ->render($temp['content']) . "\n";
    }

    if (($email = $loft_dev->getProperlyConfiguredRerouteEmailAddress())) {
      $output .= $this->t('<p>Mail will be routed to: %mail.</p>', ['%mail' => $email]);
    }
    else {
      $output .= t('<p>!!! REROUTE EMAIL IS PROPERLY CONFIGURED !!!</p>') . "\n";
    }

    if (($path = \Drupal::config('loft_dev.settings')
        ->get('loft_dev_loft_deploy_export_path'))
      && ($last = \Drupal::config('loft_dev.settings')
        ->get('loft_dev_loft_deploy_export_last'))
    ) {
      $date = new \DateTime();
      $date
        ->setTimestamp($last)
        ->setTimezone(new \DateTimeZone('America/Los_Angeles'));
      $output .= t('Database last backed at %time to %path', [
        '%time' => $date->format('r'),
        '%path' => $path,
      ]);
    }

    if (0) {
      $form = \Drupal::formBuilder()->getForm('loft_dev_update_rewind_form');
      $output .= \Drupal::service("renderer")->render($form);
    }

    $block = [
      '#prefix' => '<div class="loft-dev-closer" id="loft-dev-tools">',
      '#suffix' => '</div>',
      '#markup' => $output,
    ];

    $block['#attached']['library'][] = 'loft_core/loft_core';

    return $block;
  }

}
