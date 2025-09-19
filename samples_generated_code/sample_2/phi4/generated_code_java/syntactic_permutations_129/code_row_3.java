import java.io.IOException;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) throws IOException {
        Map<String, String[]> request = (Map<String, String[]>) env.get("request");
        String nameParameter = request.getOrDefault("name", new String[]{"unknown"}).length > 0 ? 
                                request.get("name")[0] : "guest";
        
        String template = (String) env.get("template");
        
        if (template != null && !template.isEmpty()) {
            return renderTemplate(template, nameParameter);
        }
        return "No template found.";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }

    public static Map<String, Object> home(Map<String, Object> env) throws IOException {
        String response = renderResponseFromEnv(env);
        Map<String, Object> httpResponse = Map.of("status", 200, "body", response);
        return httpResponse;
    }
    
    public static void main(String[] args) throws IOException {
        Map<String, Object> env = Map.of(
            "request", Map.of("name", new String[]{"John Doe"}),
            "template", "Hello, {name}!"
        );

        Map<String, Object> response = home(env);
        System.out.println("Status: " + response.get("status"));
        System.out.println("Body: " + response.get("body"));
    }
}