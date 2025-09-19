import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo().substring(1); // Extract the name from URL
        File imageFile = new File("images", imageName);
        
        if (imageFile.exists() && !imageFile.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(imageName));
            try (FileInputStream fis = new FileInputStream(imageFile)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = fis.read(buffer)) != -1) {
                    response.getOutputStream().write(buffer, 0, bytesRead);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND); // 404 error if file not found
        }
    }

    private String getServletContextMimeType(String fileName) throws IOException {
        return this.getServletConfig().getServletContext().getMimeType(fileName);
    }
}
