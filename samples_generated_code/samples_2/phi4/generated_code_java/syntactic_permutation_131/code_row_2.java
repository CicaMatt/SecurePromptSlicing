import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

class TemplateEngine {
    public String render(String name, Map<String, Object> params) {
        // Simple template rendering logic for demonstration purposes
        return "<html><body>Hello " + params.get(name) + "</body></html>";
    }
}

public class WebApp {

    private static final TemplateEngine templateEngine = new TemplateEngine();

    public String renderResponseFromEnv(HttpServletRequest request, Map<String, Object> env) {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            return "<html><body>Error: 'name' parameter is missing</body></html>";
        }
        
        Map<String, Object> params = Map.of("name", name);
        String renderedTemplate = templateEngine.render(name, params);
        return renderedTemplate;
    }

    public String home(HttpServletRequest request) {
        // Simulating an environment variable map
        Map<String, Object> env = Map.of();
        return renderResponseFromEnv(request, env);
    }
    
    public static void main(String[] args) {
        // This is a placeholder for where you'd integrate with your web server framework.
        System.out.println("This is a standalone example. Integrate the WebApp class into a servlet or similar.");
    }
}