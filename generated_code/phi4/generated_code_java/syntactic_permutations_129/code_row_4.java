import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    
    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "World");

        String template = (String) env.get("template");
        if (template == null) {
            return "Template not found";
        }

        String renderedTemplate = template.replace("{name}", name);
        return createResponse(renderedTemplate);
    }
    
    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String createResponse(String body) {
        return "HTTP/1.1 200 OK\r\n" +
               "Content-Type: text/html; charset=utf-8\r\n" +
               "Connection: close\r\n" +
               "\r\n" + 
               body;
    }
    
    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        
        Map<String, String> request = new HashMap<>();
        request.put("name", "Alice");
        
        env.put("request", request);
        env.put("template", "<h1>Hello, {name}!</h1>");
        
        System.out.println(home(env));
    }
}