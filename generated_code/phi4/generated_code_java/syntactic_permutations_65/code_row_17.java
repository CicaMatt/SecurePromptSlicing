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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,   // 10 MB
                 maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create the uploads directory if it does not exist
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        // Process the uploaded file
        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                Path filePath = Paths.get(uploadFilePath, fileName);
                
                try (var fileContent = part.getInputStream();
                     var outputStream = Files.newOutputStream(filePath)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = fileContent.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, bytesRead);
                    }
                } catch (IOException e) {
                    throw new ServletException("Error saving file", e);
                }

                response.getWriter().print("File " + fileName + " uploaded successfully.");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file type. Only PDF files are allowed.");
            }
        }
    }
}


This Java servlet handles file uploads from an HTML form to a specified directory on the server. It checks for PDF files and saves them in the `uploads` folder. Ensure your web server is set up to support multipart requests, and include appropriate error handling as needed.