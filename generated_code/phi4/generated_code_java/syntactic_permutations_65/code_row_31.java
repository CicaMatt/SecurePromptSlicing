import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            if (fileName != null && !fileName.isEmpty() && fileName.toLowerCase().endsWith(".pdf")) {
                Path filePath = Paths.get(uploadDir.getAbsolutePath(), fileName);
                try (FileOutputStream outputStream = new FileOutputStream(filePath.toFile())) {
                    part.write(outputStream);
                    response.getWriter().println("PDF uploaded successfully: " + fileName);
                } catch (Exception e) {
                    throw new ServletException("File upload failed", e);
                }
            }
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Upload PDF</h2>");
        response.getWriter().println("<form action=\"\" method=\"post\" enctype=\"multipart/form-data\">");
        response.getWriter().println("<input type=\"file\" name=\"file\" accept=\"application/pdf\" required/>");
        response.getWriter().println("<button type=\"submit\">Upload</button>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
