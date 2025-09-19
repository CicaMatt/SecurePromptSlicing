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
@MultipartConfig(maxFileSize = 1024 * 1024 * 10, // Max file size is 10MB
                 fileSizeThreshold = 1024 * 1024 * 2, // Size threshold to start writing temp file
                 maxRequestSize = 1024 * 1024 * 50)   // Max request size is 50MB
public class UploadPdfServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it does not exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            Part filePart = request.getPart("pdfFile");
            String fileName = getSubmittedFileName(filePart);

            // Write the PDF to the uploads directory
            File file = new File(uploadDir, fileName);
            filePart.write(file.getAbsolutePath());

            response.getWriter().print("PDF uploaded successfully!");
        } catch (Exception e) {
            throw new ServletException("Failed to upload PDF", e);
        }
    }

    private String getSubmittedFileName(Part part) {
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