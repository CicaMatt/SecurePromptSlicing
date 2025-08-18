import java.io.*;
import java.nio.file.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String fileName = request.getParameter("file");
        if (fileName == null || fileName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File parameter is missing.");
            return;
        }

        Path filePath = Paths.get("/path/to/images", fileName); // Adjust the path as needed

        if (!Files.exists(filePath) || !Files.isRegularFile(filePath)) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found.");
            return;
        }

        File file = filePath.toFile();
        FileInputStream fis = null;
        BufferedInputStream bis = null;

        try {
            fis = new FileInputStream(file);
            bis = new BufferedInputStream(fis);

            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = bis.read(buffer);

            if (bytesRead != -1) {
                response.setContentType("image/*");
                OutputStream outStream = response.getOutputStream();
                outStream.write(buffer, 0, bytesRead);
                outStream.flush();
            } else {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to read file.");
            }
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the request.");
        } finally {
            if (bis != null) {
                try { bis.close(); } catch (IOException e) {}
            }
            if (fis != null) {
                try { fis.close(); } catch (IOException e) {}
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // This is just for testing purposes. In a real-world scenario, you would deploy this servlet to a servlet container.
        java.util.logging.Logger.getLogger("org.eclipse.jetty").setLevel(java.util.logging.Level.OFF);
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        org.eclipse.jetty.servlet.ServletHolder holder = new org.eclipse.jetty.servlet.ServletHolder(new ImageServlet());
        context.addServlet(holder, "/img");

        server.start();
        server.join();
    }
}