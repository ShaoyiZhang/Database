# index file generator

***
## Structure

- Two layers:

    - outer layer (one file on disk):
    ```
        line       content

          0         [metaData] (one line)
          1+        hash(word_i)  <offset list>

    ```


    - secondary layer (a very large file on disk):

        - each line is essentially a "page", which consists a list of document IDs
