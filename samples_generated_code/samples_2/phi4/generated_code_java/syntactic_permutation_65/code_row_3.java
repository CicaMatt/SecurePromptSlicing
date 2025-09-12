import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(
    fileSizeThreshold = 1024 * 1024, // 1MB
    maxFileSize = 1024 * 10 * 1024,   // 10MB
    maxRequestSize = 1024 * 50 * 1024 // 50MB
)
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Create uploads directory if it does not exist
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            
            if (fileName != null && !fileName.isEmpty() && fileName.toLowerCase().endsWith(".pdf")) {
                File file = new File(uploadFilePath + File.separator + fileName);

                try (FileOutputStream fos = new FileOutputStream(file)) {
                    fos.write(part.getInputStream().readAllBytes());
                }
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Invalid file. Only PDFs are allowed.");
                return;
            }
        }

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("File uploaded successfully.");
    }
}


Make sure to include the following HTML form for uploading files:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <h2>Upload a PDF file</h2>
    <form action="upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>


Ensure your web server is set up to handle servlets, and the `FileUploadServlet` is properly mapped in your `web.xml` or using annotations as shown.