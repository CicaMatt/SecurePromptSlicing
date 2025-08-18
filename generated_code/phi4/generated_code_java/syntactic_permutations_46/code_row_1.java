import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/img")
public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String imageName = req.getParameter("name");
        
        if (imageName == null || imageName.isEmpty()) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing image name parameter.");
            return;
        }
        
        Path imagePath = Paths.get("images", imageName);
        if (!Files.exists(imagePath)) {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found.");
            return;
        }

        Files.copy(imagePath, resp.getOutputStream());
        resp.setContentType(getServletContext().getMimeType(imageName));
    }
}