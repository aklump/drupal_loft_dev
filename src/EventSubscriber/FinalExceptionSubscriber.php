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
      $response->headers->remove('Content-Type');
      $response->headers->add([
        'Content-Type' => 'text/html',
      ]);
    }
  }

}
