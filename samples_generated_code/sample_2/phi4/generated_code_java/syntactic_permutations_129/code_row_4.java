import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeController extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String renderedResponse = renderResponseFromEnv(request);
        response.getWriter().write(renderedResponse);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        // Retrieve the name parameter from the request
        String nameParam = request.getParameter("name");
        
        // Simulating template retrieval and rendering (for demonstration purposes)
        String template = getTemplate();
        String renderedContent = renderTemplate(template, nameParam);
        
        return createResponse(renderedContent);
    }

    private String getTemplate() {
        // For simplicity, we use a hardcoded template
        return "Hello, {{name}}!";
    }

    private String renderTemplate(String template, String name) {
        if (name != null && !name.isEmpty()) {
            return template.replace("{{name}}", name);
        }
        return template.replace("{{name}}", "Guest");
    }

    private String createResponse(String content) {
        // Simulating a response creation
        return "<html><body>" + content + "</body></html>";
    }
}