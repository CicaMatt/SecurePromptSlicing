import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadPdf")
public class PdfUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Create directory if it does not exist
        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            Part filePart = request.getPart("pdfFile");  // Retrieves <input type="file" name="pdfFile">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            
            if (fileName != null && !fileName.isEmpty()) {
                File fileToSave = new File(uploadFilePath + File.separator + fileName);

                try (var inputStream = filePart.getInputStream()) {
                    Files.copy(inputStream, fileToSave.toPath());
                }

                response.getWriter().println("File uploaded successfully!");
            } else {
                response.getWriter().println("No file was uploaded.");
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}
