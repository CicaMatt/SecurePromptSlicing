import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadPdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 10 * 1024 * 1024,      // 10 MB
                 maxRequestSize = 50 * 1024 * 1024)   // 50 MB
public class UploadPdfServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            boolean directoryCreated = fileSaveDir.mkdirs();
            if (!directoryCreated) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Could not create upload directory");
                return;
            }
        }

        String fileName = null;
        Part pdfFilePart = request.getPart("pdfFile"); // Retrieves <input type="file" name="pdfFile">
        fileName = new File(pdfFilePart.getSubmittedFileName()).getName();
        if (fileName != null && !fileName.isEmpty()) {
            try (InputStream fileContentStream = pdfFilePart.getInputStream()) {
                String filePath = uploadFilePath + File.separator + fileName;
                Files.copy(fileContentStream, Paths.get(filePath), StandardCopyOption.REPLACE_EXISTING);
            } catch (IOException ex) {
                throw new ServletException("Error saving uploaded file", ex);
            }
        }

        response.getWriter().write("File " + fileName + " has been uploaded successfully!");
    }
}
