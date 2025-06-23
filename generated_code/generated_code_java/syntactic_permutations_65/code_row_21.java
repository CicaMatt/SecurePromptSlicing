<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8" />
        <title>File Upload</title>
    </head>
    <body>
        <form action="/file_upload" method="POST" enctype="multipart/form-data">
            <input type="file" name="pdf_file" accept=".pdf"/>
            <button type="submit">Upload PDF</button>
        </form>
    </body>
</html>