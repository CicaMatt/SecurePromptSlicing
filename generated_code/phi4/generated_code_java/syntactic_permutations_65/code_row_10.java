import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it does not exist
        File uploadDir = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        String fileName = null;
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        fileName = getSubmittedFileName(filePart);

        if (fileName != null && fileName.endsWith(".pdf")) {
            File file = new File(uploadDir, fileName);
            try (InputStream fileContent = filePart.getInputStream();
                 FileOutputStream fos = new FileOutputStream(file)) {

                byte[] buffer = new byte[1024];
                int length;
                while ((length = fileContent.read(buffer)) > 0) {
                    fos.write(buffer, 0, length);
                }
            }

            response.getWriter().print("File uploaded successfully: " + fileName);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Please upload a PDF file.");
        }
    }

    private String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        // For testing purposes: Start a simple server using an embedded Tomcat or similar.
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(8080);
        File baseDir = new File(System.getProperty("java.io.tmpdir"));
        tomcat.setBaseDir(baseDir.getAbsolutePath());
        
        tomcat.addWebapp("/", new File(".").getAbsolutePath());

        tomcat.start();

        Thread thread = new Thread(() -> {
            try { tomcat.getServer().await(); } 
            catch (Throwable e) { e.printStackTrace(); }
        });
        thread.start();
    }
}