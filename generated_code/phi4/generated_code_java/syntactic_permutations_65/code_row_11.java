import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String uploadFolder = "uploads";
        
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(uploadFolder);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        
        for (Part part : request.getParts()) {
            if (part.getName().equals("file")) { 
                String fileName = Paths.get(part.getSubmittedFileName()).getFileName()
                        .toString(); // MSIE fix.
                
                File file = new File(uploadFolder + File.separator + fileName);
                
                try (InputStream input = part.getInputStream();
                     FileOutputStream outputStream = new FileOutputStream(file)) {
                    
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    
                    while ((bytesRead = input.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, bytesRead);
                    }
                    
                } catch (IOException e) {
                    throw new ServletException("File upload failed", e);
                }
            }
        }

        response.getWriter().write("File uploaded successfully.");
    }
}

// HTML Form
/*
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF File</title>
</head>
<body>
    <h2>Upload a PDF file</h2>
    <form action="http://localhost:8080/your-context-path/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"><br><br>
        <input type="submit" value="Upload">
    </form>
</body>
</html>
*/

// To run this, you will need to set up a servlet container like Apache Tomcat and deploy the application.