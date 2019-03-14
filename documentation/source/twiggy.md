# Twig Integration

* Adds support for auto-generated headers of twig templates.
* Create your twig template.
* Add the following to the top of the file:
        
        {{ file_header() }}
        
* Reload the page that renders the file.
* You twig template file should now contain a header of the available variables.
