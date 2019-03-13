Drupal.behaviors.loftDevPlayground = {
  attach: function() {
    console.log(
      Drupal.t('Playground has triggered Drupal.loftDev.hideAdminStuff.')
    );
    Drupal.loftDev.hideAdminStuff();
  },
};
