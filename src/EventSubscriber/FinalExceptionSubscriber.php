<?php

namespace Drupal\loft_dev\EventSubscriber;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\FilterResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

class FinalExceptionSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    // Run as the final (very late) KernelEvents::EXCEPTION subscriber.
    $events[KernelEvents::RESPONSE][] = ['prettifyExceptions', -256];

    return $events;
  }

  /**
   * Allows HTML to be readable by developer.
   *
   * Changes the output from text/plain to text/html for >=500 errors.
   *
   * @param \Symfony\Component\HttpKernel\Event\FilterResponseEvent $event
   */
  public function prettifyExceptions(FilterResponseEvent $event) {
    $response = $event->getResponse();
    $status = $response->getStatusCode();
    $type = $response->headers->get('Content-Type');
    if ($status >= 500 && $type === 'text/plain') {

      $content = $response->getContent();
      list($top, $backtrace) = explode('<pre class="backtrace">', $content);

      $top = str_replace('The website encountered an unexpected error. Please try again later.</br></br>', '', $top);

      $backtrace = trim(preg_replace('/<\/pre>$/', '', $backtrace));
      $backtrace = explode(PHP_EOL, $backtrace);
      $starting_count = count($backtrace) + 1;
      $backtrace = '<ol>' . implode(PHP_EOL, array_map(function ($line) {
          return "<li>$line</li>";
        }, $backtrace)) . '</ol>';

      $css = /** @lang css */
        <<<EOD
      .message {
        margin: 0 20px;
        font-size: 30px;
        line-height: 1.5;
        color: #333;
      }
      .backtrace {
        margin-top: 2em;
        font-size: 18px;
        line-height: 3;
        margin-left: 10px;
        color: #0000cc;
      }      
      .backtrace ol{
        list-style: none;
        counter-reset: reverse {$starting_count};
      }
    
      .backtrace ol> li:before {
        content: counter(reverse) '.';
        display: block;
        left: -30px;
        position: absolute;
        text-align: right;
        width: 20px;
      }
    
      .backtrace ol>li {
        counter-increment: reverse -1;
        position: relative;
      }
      EOD;


      $content = <<<EOD
        <style type="text/css">{$css}</style>
        <div class="message">{$top}</div>
        <div class="backtrace">{$backtrace}</div>
      EOD;

      $response->setContent($content);


      $response->headers->remove('Content-Type');
      $response->headers->add([
        'Content-Type' => 'text/html',
      ]);
    }
  }

}
