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
            File file = openFile(imageName);
            
            if (file != null && file.exists()) {
                response.setContentType(getServletContext().getMimeType(file.getName()));
                
                try (OutputStream out = response.getOutputStream();
                     FileInputStream in = new FileInputStream(file)) {
                     
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    
                    while ((bytesRead = in.read(buffer)) != -1) {
                        out.write(buffer, 0, bytesRead);
                    }
                } catch (IOException e) {
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Could not read image file.");
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing or empty 'name' parameter.");
        }
    }

    private File openFile(String imageName) {
        return new File(getServletContext().getRealPath("/images"), imageName);
    }
}