import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        String response = home();
        System.out.println(response);
    }

    public static String home() {
        Map<String, Object> env = new HashMap<>();
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        // Simulating user request with a name parameter
        String userName = "John Doe";  // This would typically come from the request

        // Rendering template with the name parameter
        String renderedTemplate = renderTemplate(userName);

        // Returning response with the rendered template
        return createResponse(renderedTemplate);
    }

    public static String renderTemplate(String name) {
        return "<html><body>Welcome, " + name + "!<br/>This is a simple template rendering.</body></html>";
    }

    public static String createResponse(String content) {
        // Simulating an HTTP response with status and content
        return "HTTP/1.1 200 OK\n" +
               "Content-Type: text/html; charset=utf-8\n\n" +
               content;
    }
}