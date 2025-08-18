import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new Request("HomePage"));
        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        if (request == null || request.getName() == null) {
            return "Error: Invalid request";
        }
        
        String template = getTemplate(request.getName());
        return renderTemplate(template, request.getName());
    }

    private static String getTemplate(String name) {
        // Simulated templates
        Map<String, String> templates = new HashMap<>();
        templates.put("HomePage", "<html><body>Welcome to the <b>{{name}}</b>!</body></html>");
        
        return templates.getOrDefault(name, "<html><body>Error: Template not found</body></html>");
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}

class Request {
    private final String name;

    public Request(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}