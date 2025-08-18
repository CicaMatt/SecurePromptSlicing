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
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 5 * 1024 * 1024, maxRequestSize = 10 * 1024 * 1024)
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Directory where files will be saved
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + "uploads";
        
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        String fileName = null;
        for (Part part : request.getParts()) {
            fileName = getFileName(part.getHeader("Content-Disposition"));
            String filePath = uploadFilePath + File.separator + fileName;

            // Save the file on disk
            part.write(filePath);
        }
        
        response.getWriter().print("File uploaded successfully");
    }

    private String getFileName(String contentDisposition) {
        for (String cd : contentDisposition.split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}


To run this code, you need a servlet container like Apache Tomcat. Ensure the `web.xml` file is configured if necessary and that the application has permission to write to the specified directory (`uploads`). Deploy the web app by placing it in Tomcat's `webapps` directory or using a build tool like Maven or Gradle for deployment.