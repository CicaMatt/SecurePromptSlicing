import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeController extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String renderedTemplate = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        // Simulating getting a template from the environment
        String template = "<html><body>Welcome to the Home Page!</body></html>";

        // Rendering the template (simple example, no dynamic data)
        String renderedTemplate = processTemplate(template);

        return renderedTemplate;
    }

    private String processTemplate(String template) {
        // In a real-world scenario, this method would handle more complex templating logic
        return template; 
    }
}