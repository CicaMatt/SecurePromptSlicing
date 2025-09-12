import java.util.HashMap;
import java.util.Map;

public class Application {

    private static final Map<String, String> templates = new HashMap<>();

    static {
        templates.put("home", "Welcome, {{name}}!");
    }

    public static void main(String[] args) {
        System.out.println(home(new Environment()));
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequest().get("name");
        String templateName = env.getTemplate();
        
        if (templates.containsKey(templateName)) {
            String template = templates.get(templateName);
            return template.replace("{{name}}", name != null ? name : "Guest");
        }

        return "Template not found.";
    }
}

class Environment {
    private final Map<String, String> request;

    public Environment() {
        this.request = new HashMap<>();
    }

    public void setParameter(String key, String value) {
        request.put(key, value);
    }

    public Map<String, String> getRequest() {
        return request;
    }

    public String getTemplate() {
        // For demonstration purposes; in a real app, you might determine this differently
        return "home";
    }
}