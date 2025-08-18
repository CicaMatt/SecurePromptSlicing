import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Process the file upload
        Part filePart = request.getPart("file");
        
        if (filePart != null && filePart.getSubmittedFileName().endsWith(".pdf")) {
            String fileName = File.separator + UPLOAD_DIRECTORY +
                    File.separator + filePart.getSubmittedFileName();
            
            // Create uploads directory if it doesn't exist
            File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }
            
            try (InputStream fileContent = filePart.getInputStream();
                 FileOutputStream fos = new FileOutputStream(new File(getServletContext().getRealPath(fileName)))) {

                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }

                response.getWriter().print("File uploaded successfully: " + fileName);

            } catch (Exception e) {
                throw new IOException("Error saving file", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file type. Only PDF files are allowed.");
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <h2>Upload a PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <label for="file">Choose file to upload:</label>
        <input type="file" id="file" name="file" accept=".pdf" required>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


**Note:** To run this application, you need a Java servlet container like Apache Tomcat. Make sure to configure your web.xml or use annotations as shown above for the `FileUploadServlet`. Also, ensure that your server environment is set up to handle multipart form data.