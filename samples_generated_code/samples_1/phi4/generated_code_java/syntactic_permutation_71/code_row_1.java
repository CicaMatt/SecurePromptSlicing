import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,    // 10 MB
                 maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class FileUploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = getSubmittedFileName(filePart);

        if (fileName != null && !fileName.isEmpty()) {
            File uploadDir = new File(UPLOAD_DIRECTORY);
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }

            filePart.write(new File(uploadDir, fileName));
            response.getWriter().println("File uploaded successfully!");
        } else {
            response.getWriter().println("No file uploaded.");
        }
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    @Override
    public String getServletInfo() {
        return "File Upload Servlet";
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload File</title>
</head>
<body>
<h2>Upload a file:</h2>
<form action="upload" method="post" enctype="multipart/form-data">
    <input type="file" name="file">
    <br><br>
    <button type="submit">Upload</button>
</form>
</body>
</html>


To run this application, you need a Java EE compatible server like Apache Tomcat or Jetty. Make sure to place the HTML file in the web application's root directory and configure your server accordingly.