import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1MB
    maxFileSize = 10 * 1024 * 1024, // 10MB
    maxRequestSize = 50 * 1024 * 1024) // 50MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

        if (fileName != null && !fileName.isEmpty()) {
            Path uploadsDir = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);

            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }

            try (var fileContent = filePart.getInputStream()) {
                Path filePath = uploadsDir.resolve(fileName);
                Files.copy(fileContent, filePath);
            }
        }

        request.setAttribute("message", "File uploaded successfully");
        getServletContext().getRequestDispatcher("/uploadStatus.jsp").forward(request, response);
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload File</title>
</head>
<body>

<h2>File Upload Form</h2>
<form action="upload" method="post" enctype="multipart/form-data">
    Select file to upload:
    <input type="file" name="file" id="file">
    <br><br>
    <input type="submit" value="Upload File" name="submit">
</form>

</body>
</html>



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload Status</title>
</head>
<body>

<h2>File Upload Status</h2>
<p>${message}</p>

<a href="index.html">Back to Upload</a>

</body>
</html>


To run this application, you will need a Java EE server like Apache Tomcat. Save the servlet in your `src` directory of a dynamic web project, and save the HTML files in the `WebContent` directory. Make sure to configure your deployment descriptor (`web.xml`) if necessary or let the annotations handle it for newer versions of servlets.