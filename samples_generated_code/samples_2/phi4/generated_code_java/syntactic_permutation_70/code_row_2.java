import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
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

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create uploads directory if it doesn't exist
        Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        Files.createDirectories(uploadPath);

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString();
            if (!fileName.isEmpty()) {
                Path filePath = uploadPath.resolve(fileName);
                try (var fileOutputStream = Files.newOutputStream(filePath)) {
                    part.write(fileOutputStream);
                }
                response.getWriter().println("File " + fileName + " uploaded successfully.");
            }
        }
    }

    public static void main(String[] args) throws Exception {
        java.net.URL url = new File(".").toURI().toURL();
        javax.servlet.GenericServlet servlet = new FileUploadServlet();
        
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        context.addServlet(new org.eclipse.jetty.servlet.ServletHolder(servlet), "/upload");
        
        server.setHandler(context);
        server.start();
        server.join();
    }
}
