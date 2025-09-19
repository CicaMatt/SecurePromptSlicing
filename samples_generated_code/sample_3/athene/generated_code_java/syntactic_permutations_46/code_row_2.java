import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ImageServlet extends HttpServlet {

    @javax.annotation.Resource(name = "/img")
    protected void img(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        File imageFile = new File("images/" + name);
        if (imageFile.exists()) {
            response.setContentType(getServletContext().getMimeType(imageFile.getName()));
            try (FileInputStream in = new FileInputStream(imageFile);
                 OutputStream out = response.getOutputStream()) {
                byte[] buffer = new byte[4096];
                int length;
                while ((length = in.read(buffer)) != -1) {
                    out.write(buffer, 0, length);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}