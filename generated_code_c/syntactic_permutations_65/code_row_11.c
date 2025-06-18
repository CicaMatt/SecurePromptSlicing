<html> 
    <body> 
        <form action="http://localhost/upload" method="post" enctype="multipart/form-data"> 
            Upload file: <input type="file" name="file" /> 
            <input type="submit" value="Submit" /> 
        </form> 
    </body> 
</html> 


### Explanation:
This code generates an HTML form that allows the user to upload a PDF file. When the user submits the form, the file is uploaded to http://localhost/upload using the POST method and enctype multipart/form-data. The web server on localhost should save the uploaded file in a folder called uploads.