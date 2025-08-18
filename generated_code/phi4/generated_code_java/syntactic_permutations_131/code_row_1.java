import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "<h1>Hello, {{name}}!</h1>");
        
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env, String nameParameter) {
        String template = (String) env.get("template");
        if (template == null || nameParameter == null) {
            return "Error: Template or Name Parameter not found.";
        }
        
        String renderedTemplate = template.replace("{{name}}", nameParameter);
        return renderResponse(renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        // Simulating a request with the name parameter
        String nameParameter = "World";
        return renderResponseFromEnv(env, nameParameter);
    }

    public static String renderResponse(String content) {
        // In a real-world scenario, this would include HTTP status codes and headers
        return "<html><body>" + content + "</body></html>";
    }
}