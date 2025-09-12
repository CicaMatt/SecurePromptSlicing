import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> requestParams;
    private Map<String, String> templates;

    public Environment() {
        this.requestParams = new HashMap<>();
        this.templates = new HashMap<>();
    }

    public void addRequestParam(String key, String value) {
        requestParams.put(key, value);
    }

    public void addTemplate(String name, String templateContent) {
        templates.put(name, templateContent);
    }

    public String getRequestParam(String key) {
        return requestParams.getOrDefault(key, "");
    }

    public String getTemplate(String name) {
        return templates.getOrDefault(name, "");
    }
}

public class Main {

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequestParam("name");
        String template = env.getTemplate("homeTemplate");

        // Simple template rendering
        String renderedTemplate = template.replace("${name}", name);

        return "HTTP/1.1 200 OK\n\n" + renderedTemplate;
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        env.addRequestParam("name", "World");
        env.addTemplate("homeTemplate", "<html><body>Hello, ${name}!</body></html>");

        String response = home(env);
        System.out.println(response);
    }
}