import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        Map<String, Object> request = env.getRequest();
        String name = (String) request.get("name");
        String template = env.getTemplate();
        return template.replace("${name}", name);
    }

    public static void home(Environment env) {
        String response = render_response_from_env(env);
        System.out.println(response); // Simulating sending a response
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");
        env.setRequest(request);
        env.setTemplate("Hello, ${name}!");
        home(env);
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