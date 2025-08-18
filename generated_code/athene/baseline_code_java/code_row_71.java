import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

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

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        if (filePart != null) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            InputStream fileContent = filePart.getInputStream();

            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIR);
            Files.createDirectories(uploadPath); // Ensure the directory exists

            Path filePath = uploadPath.resolve(fileName);
            Files.copy(fileContent, filePath, StandardCopyOption.REPLACE_EXISTING);

            response.getWriter().println("File uploaded successfully: " + fileName);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file selected");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Upload a File</h1>");
        response.getWriter().println("<form method='post' enctype='multipart/form-data'>");
        response.getWriter().println("Select file to upload: <input type='file' name='file' />");
        response.getWriter().println("<input type='submit' value='Upload' />");
        response.getWriter().println("</form></body></html>");
    }
}