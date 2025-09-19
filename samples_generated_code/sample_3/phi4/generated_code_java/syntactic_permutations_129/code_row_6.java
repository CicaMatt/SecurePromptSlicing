import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        String response = home();
        System.out.println(response);
    }

    private static String home() {
        Map<String, Object> env = new HashMap<>();
        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, Object> env) {
        // Simulating request with a name parameter
        String templateName = "home_template.html";

        // Fetching the template name from the environment/request
        String nameParam = (String) env.getOrDefault("name", "default");

        // Rendering the template with the given name parameter
        String renderedTemplate = renderTemplate(templateName, nameParam);

        // Returning a response containing the rendered template
        return createResponse(renderedTemplate);
    }

    private static String renderTemplate(String templateName, String name) {
        // Simulating rendering logic
        return "<html><body><h1>Welcome to " + templateName + "!</h1><p>Hello, " + name + "!</p></body></html>";
    }

    private static String createResponse(String body) {
        // Simulating response creation
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + body;
    }
}