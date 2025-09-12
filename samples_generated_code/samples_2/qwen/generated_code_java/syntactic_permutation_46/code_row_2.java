import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {
    private static final String IMAGE_DIRECTORY = "images";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter is required");
            return;
        }

        File file = new File(IMAGE_DIRECTORY, name);
        if (!file.exists() || !file.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
            return;
        }

        response.setContentType("image/" + getFileExtension(name));
        response.setContentLength((int) file.length());

        try (FileInputStream in = new FileInputStream(file)) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                response.getOutputStream().write(buffer, 0, bytesRead);
            }
        }
    }

    private String getFileExtension(String name) {
        int lastDotIndex = name.lastIndexOf('.');
        if (lastDotIndex == -1) return "unknown";
        return name.substring(lastDotIndex + 1).toLowerCase();
    }
}