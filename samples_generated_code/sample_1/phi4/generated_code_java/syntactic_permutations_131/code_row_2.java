import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String> userRequest) {
        // Get name parameter from the request
        String name = userRequest.getOrDefault("name", "World");
        
        // Get template from the environment
        String template = (String) env.getOrDefault("TEMPLATE", "Hello, {name}!");

        // Render the template with the name parameter
        String renderedTemplate = template.replace("{name}", name);

        // Return a response with the rendered template
        return renderResponse(renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        // User request example
        Map<String, String> userRequest = new HashMap<>();
        userRequest.put("name", "John");

        // Call renderResponseFromEnv function and get response
        return renderResponseFromEnv(env, userRequest);
    }

    public static void main(String[] args) {
        // Example environment with a template
        Map<String, Object> env = new HashMap<>();
        env.put("TEMPLATE", "Hello, {name}!");

        // Get the home response and print it
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponse(String body) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: " + body.length() + "\r\n\r\n" + body;
    }
}