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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,   // 10 MB
                 maxRequestSize = 50 * 1024 * 1024) // 50 MB
public class UploadPdfServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create upload directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            String fileName = "";
            Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
            fileName = getSubmittedFileName(filePart);

            // Constructs the path to save the uploaded file
            String filePath = UPLOAD_DIR + File.separator + fileName;

            if (filePath.endsWith(".pdf")) {
                // Saves the file on disk
                filePart.write(filePath);
                response.getWriter().println("PDF uploaded successfully!");
            } else {
                response.getWriter().println("Error: Only PDF files are allowed.");
            }
        } catch (IOException | ServletException e) {
            throw new ServletException("File upload failed", e);
        }
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
                return new File(fileName).getName();
            }
        }
        return null;
    }
}