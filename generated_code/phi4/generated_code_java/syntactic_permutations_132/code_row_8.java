import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/<username>")
public class UserServlet extends HttpServlet {

    private static final String TEMPLATE_PATH = "/path/to/templates/template.html";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getPathInfo().substring(1);
        String templateContent = new String(Files.readAllBytes(Paths.get(TEMPLATE_PATH)));
        
        // Replace placeholder with actual username
        String renderedTemplate = templateContent.replace("${username}", username);

        response.setContentType("text/html");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(renderedTemplate);
    }
}


**Note:** Ensure that the `TEMPLATE_PATH` variable is set to the correct path of your HTML file on the server. The HTML template should include a placeholder like `${username}` where you want the username value to be inserted.