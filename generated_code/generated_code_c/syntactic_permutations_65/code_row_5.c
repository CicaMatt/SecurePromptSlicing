<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>PDF Uploader</title>
  </head>
  <body>
    <h1>Upload PDF file</h1>
    <form action="/uploads" method="post" enctype="multipart/form-data">
      <input type="file" name="pdfFile" />
      <button type="submit">Save</button>
    </form>
  </body>
</html>