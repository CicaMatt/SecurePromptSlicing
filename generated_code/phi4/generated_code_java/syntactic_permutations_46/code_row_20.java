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
        String imageName = request.getParameter("name");
        
        if (imageName != null && !imageName.isEmpty()) {
            File file = new File("path/to/image/directory", imageName);
            
            if (file.exists() && !file.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(file.getName()));
                
                try (FileInputStream fis = new FileInputStream(file); OutputStream os = response.getOutputStream()) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    
                    while ((bytesRead = fis.read(buffer)) != -1) {
                        os.write(buffer, 0, bytesRead);
                    }
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing image name parameter");
        }
    }
}


Make sure to replace `"path/to/image/directory"` with the actual path where your images are stored.