import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    private static final String IMAGE_DIRECTORY = "images";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'name' parameter.");
            return;
        }

        File imageFile = new File(IMAGE_DIRECTORY + File.separator + name);
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }

        String mimeType = getServletContext().getMimeType(imageFile.getName());
        if (mimeType == null) {
            mimeType = "application/octet-stream";
        }
        response.setContentType(mimeType);
        response.setContentLength((int) imageFile.length());

        try (java.io.FileInputStream inStream = new java.io.FileInputStream(imageFile);
             java.io.OutputStream outStream = response.getOutputStream()) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inStream.read(buffer)) != -1) {
                outStream.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to read file.");
        }
    }
}