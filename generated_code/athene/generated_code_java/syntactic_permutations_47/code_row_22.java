import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.nio.channels.Channels;

@WebServlet("/image/*")
public class ImageServlet extends HttpServlet {
    private static final String IMAGES_FOLDER = "images";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/")) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String fileName = pathInfo.substring(1);
        File file = new File(IMAGES_FOLDER, fileName);

        if (!file.exists()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        try (FileInputStream in = new FileInputStream(file)) {
            response.setContentType(getServletContext().getMimeType(fileName));
            response.setContentLength((int) file.length());
            in.transferTo(Channels.newChannel(response.getOutputStream()));
        }
    }
}