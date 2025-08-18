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

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = getFileName(filePart);
        File uploadsDir = new File(UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }
        String filePath = UPLOAD_DIR + File.separator + fileName;
        filePart.write(filePath);

        // Save the filepath in a session or database for later use
        request.getSession().setAttribute("pdfFilePath", filePath);

        response.sendRedirect("upload_success.jsp");
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String filePath = (String) request.getSession().getAttribute("pdfFilePath");
        if (filePath != null) {
            File file = new File(filePath);
            if (file.exists()) {
                response.setContentType("application/pdf");
                response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");
                response.setContentLength((int) file.length());
                try (java.io.FileInputStream fis = new java.io.FileInputStream(file);
                     java.io.OutputStream out = response.getOutputStream()) {
                    byte[] buffer = new byte[4096];
                    int count;
                    while ((count = fis.read(buffer)) != -1) {
                        out.write(buffer, 0, count);
                    }
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            }
        } else {
            response.sendRedirect("upload_pdf.jsp?error=No file uploaded");
        }
    }
}