import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/images/*")
public class ImageServlet extends HttpServlet {
    private static final String IMAGES_FOLDER = "path/to/images/folder";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Get the requested resource path from the URL pattern
        String imagePath = IMAGES_FOLDER + request.getPathInfo();
        File imageFile = new File(imagePath);

        if (imageFile.exists() && !imageFile.isDirectory()) {
            // Set content type based on file extension (assuming JPEG for simplicity)
            response.setContentType("image/jpeg");
            // Send the file to the browser
            javax.servlet.http.Part part = request.getPart("file"); // This is just a placeholder, actual use may vary
            java.io.InputStream inputStream = imageFile.toURI().toURL().openStream();
            java.io.OutputStream outputStream = response.getOutputStream();
            byte[] buffer = new byte[1024];
            int length;
            while ((length = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, length);
            }
            inputStream.close();
            outputStream.close();
        } else {
            // If file doesn't exist, send a 404 error
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
