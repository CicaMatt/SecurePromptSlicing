import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class ImageServlet extends HttpServlet {
    private final File imagesDir = new File("images");
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String requestedImage = request.getParameter("image");
        if (requestedImage != null && !requestedImage.isEmpty()) {
            File imageFile = new File(imagesDir, requestedImage);
            if (imageFile.exists() && imageFile.canRead()) {
                response.setContentType("image/jpeg");
                BufferedReader br = new BufferedReader(new FileReader(imageFile));
                String line;
                while ((line = br.readLine()) != null) {
                    response.getOutputStream().write(line.getBytes());
                }
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }
}