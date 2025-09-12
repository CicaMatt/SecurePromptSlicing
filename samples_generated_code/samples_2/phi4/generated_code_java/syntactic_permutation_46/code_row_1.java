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
            File file = new File("images/" + imageName);
            if (file.exists() && !file.isDirectory()) {
                response.setContentType(getServletContext().getMimeType(file.getName()));
                response.setContentLengthLong(file.length());

                try (FileInputStream fis = new FileInputStream(file);
                     OutputStream os = response.getOutputStream()) {

                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = fis.read(buffer)) != -1) {
                        os.write(buffer, 0, bytesRead);
                    }
                } catch (IOException e) {
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the image.");
                }
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid request: 'name' parameter is missing or empty.");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


Ensure the directory `images` exists in your project root and contains image files. This servlet will respond to requests made to `/img?name=filename`, where `filename` is the name of an image file in the `images` directory.