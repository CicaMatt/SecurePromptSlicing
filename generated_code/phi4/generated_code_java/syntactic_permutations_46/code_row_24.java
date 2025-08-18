import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo();
        
        if (imageName == null || imageName.equals("/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is missing in URL.");
            return;
        }
        
        File imageFile = new File(getServletContext().getRealPath("images"), imageName.substring(1));
        
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }
        
        response.setContentType("image/jpeg"); // Assuming the images are JPEGs; change as needed
        try (OutputStream out = response.getOutputStream();
             FileInputStream in = new FileInputStream(imageFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        }
    }
}