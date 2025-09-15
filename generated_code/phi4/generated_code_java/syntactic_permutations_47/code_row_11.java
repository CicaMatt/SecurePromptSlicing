import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/fileDownload")
public class FileDownloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = "path/to/your/file.txt"; // Specify the file path here

        File file = new File(filePath);

        if (file.exists()) {
            response.setContentType("application/octet-stream");
            response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");

            try (FileInputStream inStream = new FileInputStream(file)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    response.getOutputStream().write(buffer, 0, bytesRead);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
        }
    }

    public static void main(String[] args) throws Exception {
        // This is a basic setup for running the servlet in a local environment.
        // For production use, it should be deployed on a proper server like Apache Tomcat.

        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);

        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(FileDownloadServlet.class), "/fileDownload");
        
        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }
}
