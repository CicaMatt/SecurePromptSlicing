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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,      // 10 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Create uploads directory if it doesn't exist
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        Part part = request.getPart("pdfFile");
        String fileName = extractFileName(part);

        // Rename file to avoid duplicates
        File fileToCreate = new File(fileSaveDir + File.separator + fileName);
        int suffix = 1;
        while (fileToCreate.exists()) {
            fileName = "copy_" + suffix++ + "_" + fileName;
            fileToCreate = new File(fileSaveDir + File.separator + fileName);
        }

        part.write(uploadFilePath + File.separator + fileName);

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>File " + fileName + " has uploaded successfully!</h2>");
        response.getWriter().println("</body></html>");
    }

    private String extractFileName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        String[] items = contentDisp.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>FileUploadServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>
</web-app>