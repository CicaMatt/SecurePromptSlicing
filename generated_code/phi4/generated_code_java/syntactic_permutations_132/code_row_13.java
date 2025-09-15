import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            response.setContentType("text/html");
            
            // Read the template file
            String templateContent;
            try {
                templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            } catch (IOException e) {
                throw new ServletException("Unable to read template file", e);
            }
            
            // Replace placeholder with username
            String personalizedContent = templateContent.replace("{username}", username);

            response.getWriter().write(personalizedContent);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Resource not found");
        }
    }

}
