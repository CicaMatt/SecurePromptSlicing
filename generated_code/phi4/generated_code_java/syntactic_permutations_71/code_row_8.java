import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;

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
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create a path for file storage
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        // Check if the uploads directory exists, create it if not
        File uploadDir = new File(uploadFilePath);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        // Process the file upload request
        for (Part part : request.getParts()) {
            String fileName = getSubmittedFileName(part);

            if (fileName != null && !fileName.isEmpty()) {
                part.write(uploadFilePath + File.separator + fileName);
            }
        }

        response.getWriter().print("File uploaded successfully!");
    }

    private static String getSubmittedFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim()
                        .replace("\"", "");
            }
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        // This is for testing purposes only. In a real deployment, use an application server.
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
            new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);

        context.setContextPath("/");
        server.setHandler(context);

        // Add the servlet to handle file uploads
        context.addServlet(new org.eclipse.jetty.servlet.ServletHolder(FileUploadServlet.class), "/upload");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }
}
