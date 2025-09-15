import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.nio.file.*;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getParameter("name");
        
        if (imageName == null || imageName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing name parameter.");
            return;
        }

        Path imagePath = Paths.get(getServletContext().getRealPath("/images"), imageName);

        if (!Files.exists(imagePath) || !Files.isRegularFile(imagePath)) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }
        
        try (InputStream fileStream = new FileInputStream(imagePath.toFile())) {
            byte[] buffer = new byte[4096];
            int bytesRead;

            // Set content type based on the image extension
            String contentType = getServletContext().getMimeType(imagePath.toString());
            if (contentType == null) {
                contentType = "application/octet-stream";
            }
            response.setContentType(contentType);

            // Write file contents to output stream
            ServletOutputStream outStream = response.getOutputStream();
            while ((bytesRead = fileStream.read(buffer)) != -1) {
                outStream.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            throw new ServletException("Error reading image file", e);
        }
    }
}
