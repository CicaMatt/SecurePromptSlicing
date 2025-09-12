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
    private static final String IMAGE_FOLDER = "path/to/your/images/folder/";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = IMAGE_FOLDER + request.getPathInfo();
        File file = new File(filePath);
        
        if (file.exists() && !file.isDirectory()) {
            response.setContentType(getServletContext().getMimeType(file.getName()));
            response.setContentLength((int) file.length());
            
            try (FileInputStream inStream = new FileInputStream(file)) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    response.getOutputStream().write(buffer, 0, bytesRead);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
        }
    }
}