import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "./";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        if (filePart != null && filePart.getSize() > 0) {
            String fileName = getFileName(filePart);
            if (fileName.endsWith(".pdf")) {
                InputStream fileContent = filePart.getInputStream();
                File uploadDir = new File(UPLOAD_DIRECTORY);
                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }
                File uploadedFile = new File(uploadDir + File.separator + fileName);
                try (FileOutputStream fos = new FileOutputStream(uploadedFile)) {
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = fileContent.read(buffer)) != -1) {
                        fos.write(buffer, 0, bytesRead);
                    }
                }
                response.getWriter().println("File uploaded successfully: " + fileName);
            } else {
                response.getWriter().println("Only PDF files are allowed.");
            }
        } else {
            response.getWriter().println("No file selected or the file is empty.");
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        javax.swing.SwingUtilities.invokeLater(() -> {
            try {
                org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
                tomcat.setPort(8080);
                tomcat.getConnector();

                Context ctx = tomcat.addContext("", System.getProperty("java.io.tmpdir"));

                Tomcat.addServlet(ctx, "FileUploadServlet", new FileUploadServlet());
                ctx.addServletMappingDecoded("/upload", "FileUploadServlet");

                tomcat.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}