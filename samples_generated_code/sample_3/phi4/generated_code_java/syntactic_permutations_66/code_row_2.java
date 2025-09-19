import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadPdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 10 * 1024 * 1024)
public class PdfUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create uploads directory if it does not exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Process the uploaded file
        for (Part part : request.getParts()) {
            String fileName = extractFileName(part);

            if (fileName != null && fileName.endsWith(".pdf")) {
                String filePath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY + File.separator + fileName;
                
                File file = new File(filePath);
                try (var output = new java.io.FileOutputStream(file)) {
                    part.write(output);
                }
            } else {
                response.getWriter().println("Invalid file type. Only PDF files are allowed.");
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            }
        }

        response.getWriter().println("File uploaded successfully");
    }

    private String extractFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim();
                fileName = fileName.replace("\"", "");
                return fileName;
            }
        }
        return null;
    }
}
