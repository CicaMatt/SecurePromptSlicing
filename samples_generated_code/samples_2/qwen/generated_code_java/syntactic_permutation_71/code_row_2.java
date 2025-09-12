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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
        maxFileSize = 1024 * 1024 * 10,      // 10MB
        maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String appPath = request.getServletContext().getRealPath("");
        String uploadFilePath = appPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        Part filePart = request.getPart("file");
        String fileName = extractFileName(filePart);

        filePart.write(uploadFilePath + File.separator + fileName);
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h3 style='color:green;'>File " + fileName
                + " has uploaded successfully!</h3>");
        response.getWriter().println("</body></html>");
    }

    private String extractFileName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        String[] items = contentDisp.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf("=") + 2, s.length() - 1);
            }
        }
        return "";
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>File Upload</h1>");
        response.getWriter().println("<form action='upload' method='post' enctype='multipart/form-data'>");
        response.getWriter().println("<input type='file' name='file' size='60' />");
        response.getWriter().println("<br/>");
        response.getWriter().println("<input type='submit' value='Upload' />");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}