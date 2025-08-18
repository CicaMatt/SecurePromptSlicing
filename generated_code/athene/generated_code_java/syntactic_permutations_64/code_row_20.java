import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_pdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
maxFileSize = 1024 * 1024 * 10,      // 10MB
maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class PDFUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        File uploadsDir = new File(UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File uploadedFile = new File(uploadsDir, fileName);
        filePart.write(uploadedFile.getAbsolutePath());

        // Save the filepath to a database or session
        request.getSession().setAttribute("pdfFilePath", uploadedFile.getAbsolutePath());

        response.sendRedirect(request.getContextPath() + "/upload_success.jsp");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String pdfFilePath = (String) request.getSession().getAttribute("pdfFilePath");
        if (pdfFilePath != null) {
            File file = new File(pdfFilePath);
            if (file.exists()) {
                response.setContentType("application/pdf");
                response.setHeader("Content-Disposition", "attachment; filename=" + file.getName());
                Files.copy(file.toPath(), response.getOutputStream());
                response.getOutputStream().flush();
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "PDF file not found");
        }
    }
}