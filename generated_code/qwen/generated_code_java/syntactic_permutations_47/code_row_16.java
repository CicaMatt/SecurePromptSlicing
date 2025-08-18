import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/images/*")
public class ImageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imagePath = getServletContext().getRealPath("/images/") + request.getPathInfo();
        File imageFile = new File(imagePath);
        
        if (imageFile.exists()) {
            response.setContentType("image/*");
            response.setContentLength((int) imageFile.length());
            
            try (FileInputStream inStream = new FileInputStream(imageFile)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    response.getOutputStream().write(buffer, 0, bytesRead);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
        }
    }
}