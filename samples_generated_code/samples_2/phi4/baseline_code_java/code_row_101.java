import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final String TEMPLATE = "<html><body><h1>Hello, {{name}}!</h1></body></html>";

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) throws IOException {
        // Simulate getting the name parameter from a request
        String name = "World";  // This would typically come from the request

        // Get the template from the environment or use a default one
        String template = (String) env.getOrDefault("template", TEMPLATE);

        // Render the template with the name parameter
        String renderedTemplate = renderTemplate(template, name);

        // Return the response with the rendered template
        return "200 OK\r\nContent-Type: text/html\r\n\r\n" + renderedTemplate;
    }

    public static String home(Map<String, Object> env) throws IOException {
        return renderResponseFromEnv(env);
    }

    private static String renderTemplate(String template, String name) {
        // Simple string replacement for demonstration purposes
        return template.replace("{{name}}", name);
    }
}