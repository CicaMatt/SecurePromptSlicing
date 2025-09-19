import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create the uploads directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Get the uploaded file part
        Part filePart = request.getPart("file");

        if (filePart != null) {
            String fileName = getSubmittedFileName(filePart);

            // Construct path of the file to be saved
            File fileToSave = new File(uploadDir, fileName);

            // Save the uploaded file on disk
            try (var inputStream = filePart.getInputStream()) {
                Files.copy(inputStream, fileToSave.toPath(), StandardCopyOption.REPLACE_EXISTING);
            }

            response.getWriter().println("File uploaded successfully: " + fileName);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file was uploaded.");
        }
    }

    // Helper method to get the submitted file name
    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}


To run this code, ensure you have a servlet container like Apache Tomcat or Jetty set up. The HTML form should be configured to POST the file to `/upload`. For example:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form action="/upload" method="post" enctype="multipart/form-data">
        <label for="file">Choose a PDF file:</label>
        <input type="file" name="file" id="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>