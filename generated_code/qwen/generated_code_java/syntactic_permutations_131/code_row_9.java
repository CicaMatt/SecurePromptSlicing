import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env, Map<String, String> requestParams) {
        String name = requestParams.get("name");
        String template = env.getTemplate();
        return template.replace("{name}", name);
    }

    public static String home(Environment env, Map<String, String> requestParams) {
        return render_response_from_env(env, requestParams);
    }

    public static void main(String[] args) {
        Environment env = new Environment("<html><body>Hello, {name}!</body></html>");
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "World");
        
        String response = home(env, requestParams);
        System.out.println(response);
    }
}

class Environment {
    private final String template;

    public Environment(String template) {
        this.template = template;
    }

    public String getTemplate() {
        return template;
    }
}