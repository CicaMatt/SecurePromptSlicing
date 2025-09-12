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
        
        if (imageName == null || imageName.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Image name is required.");
            return;
        }
        
        File imageFile = new File(getServletContext().getRealPath("/images") + File.separator + imageName);
        
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }

        response.setContentType("image/jpeg"); // You might want to set this dynamically based on file type
        OutputStream out = response.getOutputStream();
        try (FileInputStream in = new FileInputStream(imageFile)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        } finally {
            out.close();
        }
    }
}