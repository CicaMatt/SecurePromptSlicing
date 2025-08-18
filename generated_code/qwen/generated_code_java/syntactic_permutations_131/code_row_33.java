import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> templates = new HashMap<>();

    public Environment() {
        templates.put("greeting", "Hello, %s!");
    }

    public String getTemplate(String name) {
        return templates.get(name);
    }
}

public class Main {

    public static String render_response_from_env(Environment env, Map<String, String> requestParams) {
        String name = requestParams.get("name");
        String template = env.getTemplate("greeting");
        if (template != null && name != null) {
            return template.formatted(name);
        }
        return "Hello, World!";
    }

    public static String home(Environment env, Map<String, String> requestParams) {
        return render_response_from_env(env, requestParams);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "Alice");
        String response = home(env, requestParams);
        System.out.println(response);
    }
}