import java.io.File;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/image")
public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String fileName = request.getParameter("name");
        if (fileName == null || fileName.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File name is required");
            return;
        }

        File file = new File(getServletContext().getRealPath("/images"), fileName);

        if (!file.exists() || !file.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
            return;
        }

        response.setContentType("image/jpeg");  // or another appropriate MIME type
        response.setHeader("Content-Disposition", "inline; filename=\"" + file.getName() + "\"");

        java.nio.file.Files.copy(file.toPath(), response.getOutputStream());
    }
}


To make this code runnable, ensure you have a Java servlet container like Apache Tomcat set up and properly configured. Place the above class in your web application's `src` directory (or appropriate package location), compile it, and deploy it to your server. The images should be placed in an "images" folder at the root of your web context for this code to work as expected.