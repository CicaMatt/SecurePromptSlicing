import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.io.InputStream;

public class FileUploadServer {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(FileUploadServlet.class), "/upload");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

}

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Create the directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try (Part filePart = request.getPart("file")) { // Retrieves <input type="file" name="file">
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            File uploadedFile = new File(uploadDir, fileName);

            try (InputStream fileContent = filePart.getInputStream();
                 FileOutputStream fos = new FileOutputStream(uploadedFile)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }

            response.getWriter().print("Upload has been done successfully!");
        } catch (Exception e) {
            throw new ServletException("File upload failed", e);
        }
    }
}


To run this code:

1. Ensure you have the Jetty server and Servlet API dependencies in your project's classpath.
2. Save the code to a file, for example `FileUploadServer.java`.
3. Compile it with `javac FileUploadServer.java`.
4. Run the compiled class with `java FileUploadServer`.

Make sure you have an HTML form that matches this servlet path and uses `POST` method with `enctype="multipart/form-data"` to allow file uploads:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
<form action="http://localhost:8080/upload" method="post" enctype="multipart/form-data">
    <input type="file" name="file" />
    <button type="submit">Upload</button>
</form>
</body>
</html>