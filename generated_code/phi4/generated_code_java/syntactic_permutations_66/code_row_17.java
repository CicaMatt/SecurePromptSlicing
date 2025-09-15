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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = System.getProperty("user.dir") + "/uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
            String fileName = getSubmittedFileName(filePart);

            if (fileName != null && fileName.endsWith(".pdf")) {
                File file = new File(UPLOAD_DIRECTORY + File.separator + fileName);
                
                try (var output = new java.io.FileOutputStream(file)) {
                    var input = filePart.getInputStream();
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    
                    while ((bytesRead = input.read(buffer)) != -1) {
                        output.write(buffer, 0, bytesRead);
                    }
                }

                response.getWriter().println("File uploaded successfully: " + fileName);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file type. Only PDFs are allowed.");
            }
        } catch (Exception e) {
            throw new ServletException("Failed to upload file", e);
        }
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim()
                        .replace("\"", "");
            }
        }
        return null;
    }
}
