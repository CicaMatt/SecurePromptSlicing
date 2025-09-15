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
