import java.io.File;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/image")
public class ImageServlet extends HttpServlet {
    private static final String IMAGE_FOLDER = "images";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, java.io.IOException {

        // Get the file name from the URL parameter
        String fileName = request.getParameter("file");

        if (fileName == null || fileName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File parameter is missing");
            return;
        }

        File imageFile = new File(IMAGE_FOLDER + File.separator + fileName);

        // Check if the file exists
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            return;
        }

        // Set content type and send the file to the browser
        response.setContentType("image/jpeg");  // Assuming images are JPEGs; adjust as needed
        response.setHeader("Content-Disposition", "inline; filename=\"" + fileName + "\"");

        java.io.FileInputStream fileInputStream = new java.io.FileInputStream(imageFile);
        java.nio.channels.Channels.copy(fileInputStream.getChannel(), response.getOutputStream().getChannel());
        
        fileInputStream.close();
    }
}


To make this code runnable, ensure the following:
- This servlet is part of a web application deployed on a Java EE-compatible server (like Tomcat).
- The `images` folder exists within your web application's directory and contains image files.