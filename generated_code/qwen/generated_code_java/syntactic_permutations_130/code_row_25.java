import java.util.HashMap;
import java.util.Map;

public class Environment {
    private Map<String, Object> requestParams;
    private String template;

    public Environment(Map<String, Object> requestParams, String template) {
        this.requestParams = requestParams;
        this.template = template;
    }

    public Map<String, Object> getRequestParams() {
        return requestParams;
    }

    public String getTemplate() {
        return template;
    }
}

class Renderer {
    public static String render(String template, Map<String, Object> context) {
        // Simple placeholder for rendering logic
        return template.replace("{name}", (String) context.get("name"));
    }
}

public class Application {

    public static String renderResponseFromEnv(Environment env) {
        String name = (String) env.getRequestParams().get("name");
        String template = env.getTemplate();
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        return Renderer.render(template, context);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> requestParams = new HashMap<>();
        requestParams.put("name", "World");
        Environment env = new Environment(requestParams, "Hello, {name}!");
        String response = home(env);
        System.out.println(response);
    }
}