import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Environment env = new Environment();
        String response = home(env);
        System.out.println(response);
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Environment env) {
        Map<String, String> requestParams = env.getRequestParameters();
        String name = requestParams.get("name");
        
        String template = env.getTemplate();
        String renderedTemplate = template.replace("{name}", name != null ? name : "Guest");
        
        return renderedTemplate;
    }
}

class Environment {
    private static final Map<String, String> templates = new HashMap<>();
    private static final Map<String, String> requestParams = new HashMap<>();

    public Environment() {
        templates.put("home", "<h1>Welcome, {name}!</h1>");
        // Simulating a request parameter
        requestParams.put("name", "John Doe");
    }

    public Map<String, String> getRequestParameters() {
        return requestParams;
    }

    public String getTemplate() {
        return templates.getOrDefault("home", "");
    }
}