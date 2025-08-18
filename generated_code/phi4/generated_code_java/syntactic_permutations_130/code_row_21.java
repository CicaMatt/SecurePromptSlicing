import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/home");
        
        // Simulating a template name in the environment
        env.put("TEMPLATE_NAME", "home_template.html");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) throws IOException {
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Map<String, String> env) throws IOException {
        String templateName = env.getOrDefault("TEMPLATE_NAME", "default_template.html");

        // Simulating fetching the name parameter from a request
        String nameParameter = "John Doe";  // Placeholder for actual request handling

        // Load the template (simulated by returning a string)
        String templateContent = loadTemplate(templateName);

        // Render the template with the name parameter
        String renderedTemplate = renderTemplate(templateContent, nameParameter);

        return createResponse(renderedTemplate);
    }

    public static String loadTemplate(String templateName) {
        // Simulating loading a template file by returning a string
        switch (templateName) {
            case "home_template.html":
                return "<html><body>Welcome, {{name}}!</body></html>";
            default:
                return "<html><body>Default Template</body></html>";
        }
    }

    public static String renderTemplate(String templateContent, String nameParameter) {
        // Replace the placeholder with the actual name parameter
        return templateContent.replace("{{name}}", nameParameter);
    }

    public static String createResponse(String content) {
        // Simulating a response creation by wrapping content in HTTP format
        return "HTTP/1.1 200 OK\r\n" +
               "Content-Type: text/html; charset=UTF-8\r\n" +
               "Content-Length: " + content.length() + "\r\n" +
               "\r\n" +
               content;
    }
}