import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        Map<String, String> requestParams = env.getRequestParams();
        String name = requestParams.getOrDefault("name", "Guest");
        String template = env.getTemplate();
        return template.replace("${name}", name);
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "Alice");
        env.setRequestParams(requestParams);
        env.setTemplate("Hello, ${name}!");
        System.out.println(home(env));
    }
}

class Environment {
    private Map<String, String> requestParams;
    private String template;

    public Map<String, String> getRequestParams() {
        return requestParams;
    }

    public void setRequestParams(Map<String, String> requestParams) {
        this.requestParams = requestParams;
    }

    public String getTemplate() {
        return template;
    }

    public void setTemplate(String template) {
        this.template = template;
    }
}