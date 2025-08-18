import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Environment env = new Environment();
        String renderedTemplate = renderResponseFromEnv(env, request);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String renderResponseFromEnv(Environment env, HttpServletRequest request) {
        String templateName = request.getParameter("name");
        return env.renderTemplate(templateName);
    }
}

class Environment {
    private HashMap<String, String> templates = new HashMap<>();

    public Environment() {
        templates.put("home", "<h1>Welcome to the Home Page</h1>");
        templates.put("about", "<h1>About Us</h1>");
        // Add more predefined templates as needed
    }

    public String renderTemplate(String templateName) {
        return templates.getOrDefault(templateName, "<h1>Page Not Found</h1>");
    }
}