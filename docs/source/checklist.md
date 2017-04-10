## Drupal Block
To see the checklist in drupal, assign the block to a valid region.

## Configuration XML
A private file needs to be created at: `private::loft_dev/page_review/checklist.xml` using the following pattern.

    <config>
      <status value="0">not started</status>
      <status value="1">done</status>
      <page/>
      <page/>
    </config>  

### Each XML `<status/>` defines a status code/name
Define the status values in the xml, which are then used in the page nodes.

### Each XML `<page/>` consists of

    <page weight="12">
      <status>1</status>
      <title>Theme</title>
      <comp>https://www.globalonenessproject.org/node/3139</comp>
      <notes>{uri}</notes>
      <guide>{uri}</guide>
      <uri>node/3139</uri>
    </page>

| attribute | description | example |
|----------|----------|----------|
| weight | The sort order | 3 |

| child | description | example |
|----------|----------|----------|
| status | The pages development status | 1 |
| title | A description for the page | User signup |
| uri* | url to the drupal page  | {url}  |
| guide* | url to pattern lab guide | {url} |
| comp* | url to a comp | {url} |
| notes* | url to notes | {url} |

* allows multiple nodes.

## Status values
| status | meaning |
|----------|----------|
| 0 | in dev |
| 1 | done |
| 2 | prototype in process |
| 3 | prototype finished |
| 4 | minor css needed |
