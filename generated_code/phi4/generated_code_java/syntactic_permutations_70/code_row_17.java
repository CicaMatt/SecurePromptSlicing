import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadFile")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            String filePath = uploadsDir.getAbsolutePath() + File.separator + fileName;
            filePart.write(filePath);

            response.getWriter().print("File uploaded successfully.");
        } else {
            response.getWriter().print("No file uploaded.");
        }
    }
}


**Additional Setup:**

1. **Directory Structure:** Ensure you have a directory named `uploads` in the web application's root directory to store the uploaded files.

2. **Web Deployment Descriptor (`web.xml`):**
   If not using annotations, configure your servlet in `web.xml`.

3. **HTML Form for Uploading Files:**


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <form action="uploadFile" method="post" enctype="multipart/form-data">
        <input type="file" name="file">
        <button type="submit">Upload</button>
    </form>
</body>
</html>


4. **Server Setup:** Deploy this code to a Java servlet container like Apache Tomcat.

5. **Dependencies:** Ensure you have the necessary libraries for running servlets, typically provided by your server or included in a build tool configuration (e.g., Maven/Gradle).