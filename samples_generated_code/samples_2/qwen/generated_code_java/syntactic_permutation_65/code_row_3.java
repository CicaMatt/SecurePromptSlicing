import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
                 maxFileSize = 1024 * 1024 * 10,      // 10MB
                 maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class FileUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try (InputStream inputStream = filePart.getInputStream();
             FileOutputStream outputStream = new FileOutputStream(new File(uploadFilePath + File.separator + fileName))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

        } catch (IOException e) {
            response.getWriter().println("File upload failed due to " + e.getMessage());
            return;
        }
        response.getWriter().println("File uploaded successfully");
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
<form action="upload" method="post" enctype="multipart/form-data">
    Select a PDF file to upload:
    <input type="file" name="file" accept=".pdf" required>
    <button type="submit">Upload File</button>
</form>
</body>
</html>