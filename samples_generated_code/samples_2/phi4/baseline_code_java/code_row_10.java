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
        if (imageName != null && !imageName.trim().isEmpty()) {
            File imageFile = new File("images/" + imageName);
            if (imageFile.exists() && !imageFile.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(imageName));
                try (OutputStream out = response.getOutputStream();
                     FileInputStream in = new FileInputStream(imageFile)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = in.read(buffer)) != -1) {
                        out.write(buffer, 0, bytesRead);
                    }
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter is missing or empty");
        }
    }
}