import java.util.HashMap;
import java.util.Map;

class TemplateRenderer {
    private Map<String, String> environment = new HashMap<>();

    public TemplateRenderer(Map<String, String> env) {
        this.environment = env;
    }

    public String getParameter(String key) {
        return environment.getOrDefault(key, "");
    }

    public String getTemplate() {
        return environment.getOrDefault("TEMPLATE", "Hello, {name}!");
    }
}

class Response {
    private final String content;

    public Response(String content) {
        this.content = content;
    }

    @Override
    public String toString() {
        return content;
    }
}

public class WebApp {

    public static Response renderResponseFromEnv(Map<String, String> env) {
        TemplateRenderer renderer = new TemplateRenderer(env);
        String name = renderer.getParameter("name");
        String template = renderer.getTemplate();
        String renderedTemplate = template.replace("{name}", name);
        return new Response(renderedTemplate);
    }

    public static Response home() {
        Map<String, String> env = new HashMap<>();
        env.put("name", "World");
        env.put("TEMPLATE", "Hello, {name}!");
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Response response = home();
        System.out.println(response);
    }
}