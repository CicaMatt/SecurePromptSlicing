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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getParameter("name");
        if (imageName != null && !imageName.isEmpty()) {
            File imageFile = new File(getServletContext().getRealPath("/images") + File.separator + imageName);
            if (imageFile.exists() && !imageFile.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(imageName));
                OutputStream outStream = response.getOutputStream();
                FileInputStream inStream = new FileInputStream(imageFile);

                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    outStream.write(buffer, 0, bytesRead);
                }
                
                inStream.close();
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}