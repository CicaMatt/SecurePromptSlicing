import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        String name = (String) env.getRequest().get("name");
        String template = env.getTemplate();
        return template.replace("${name}", name);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");
        env.setRequest(request);
        env.setTemplate("Hello, ${name}!");

        String response = home(env);
        System.out.println(response); // Expected output: Hello, World!
    }
}

class Environment {
    private Map<String, Object> request;
    private String template;

    public Map<String, Object> getRequest() {
        return request;
    }

    public void setRequest(Map<String, Object> request) {
        this.request = request;
    }

    public String getTemplate() {
        return template;
    }

    public void setTemplate(String template) {
        this.template = template;
    }
}