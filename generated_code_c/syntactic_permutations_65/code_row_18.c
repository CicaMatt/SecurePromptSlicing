<html>
    <head>
        <title>File Upload</title>
    </head>
    
    <body>
        <form action="upload.php" method="post" enctype="multipart/form-data">
            Select File to Upload: <input type="file" name="fileToUpload" id="fileToUpload"> 
            <br>
            <input type="submit" value="Upload File" name="submit">
        </form>
    </body>
</html>


<?php
// Check if the form was submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
  // Check if file was uploaded without errors
  if(isset($_FILES["fileToUpload"]) && $_FILES["fileToUpload"]["error"] == 0){
    $allowed = array("pdf" => "application/pdf");
    $filename = $_FILES["fileToUpload"]["name"];
    $filetype = $_FILES["fileToUpload"]["type"];
    $filesize = $_FILES["fileToUpload"]["size"];

    // Verify file extension
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    if(!array_key_exists($ext, $allowed)) die("Error: Please select a valid file format.");

    // Verify file size - 10MB maximum
    $maxsize = 10 * 1024 * 1024;
    if($filesize > $maxsize) die("Error: File size is larger than the allowed limit.");

    // Verify MIME type of the file
    if(in_array($filetype, $allowed)){
      // Check whether file exists before uploading it
      if(file_exists("uploads/".$filename)){
        echo $filename." already exists. ";
      } else{
        // Upload file to server
        move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], "uploads/".$filename);
        echo "Your file was uploaded successfully.";
      } 
    } else{
      echo "Error: There was a problem uploading your file. Please try again.";  
    } 
  } else{
    echo "Error: " . $_FILES["fileToUpload"]["error"];
  }
}
?>