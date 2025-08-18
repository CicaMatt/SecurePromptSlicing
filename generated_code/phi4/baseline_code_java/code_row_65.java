import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadPath = "uploads";
        Path uploadsDir = Paths.get(uploadPath);
        
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        for (Part part : request.getParts()) {
            String fileName = getSubmittedFileName(part);
            if (fileName != null && fileName.endsWith(".pdf")) {
                try (InputStream input = part.getInputStream();
                     FileOutputStream output = new FileOutputStream(new File(uploadPath, fileName))) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = input.read(buffer)) != -1) {
                        output.write(buffer, 0, bytesRead);
                    }
                }
            }
        }

        response.setContentType("text/html");
        response.getWriter().println("<h2>File uploaded successfully!</h2>");
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
                return fileName;
            }
        }
        return null;
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PDF Upload</title>
</head>
<body>
    <h2>Upload PDF File</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf"><br><br>
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Make sure your `web.xml` (if using Servlet 2.5) or annotations are properly configured for the servlet to map correctly to `/upload`. Ensure you have a local server running, such as Apache Tomcat, and place these files in the appropriate directories within your web application structure.