import java.io.File;
import java.io.FileInputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.file.Files;

@WebServlet("/image")
public class ImageServlet extends HttpServlet {
    
    private static final String IMAGES_FOLDER = "path/to/images/folder/";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getParameter("name");
        
        if (imageName != null && !imageName.isEmpty()) {
            File imageFile = new File(IMAGES_FOLDER + imageName);
            
            if (imageFile.exists() && !imageFile.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(imageName));
                try (FileInputStream fileInputStream = new FileInputStream(imageFile)) {
                    Files.copy(fileInputStream.getChannel(), response.getOutputStream());
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is required");
        }
    }
}