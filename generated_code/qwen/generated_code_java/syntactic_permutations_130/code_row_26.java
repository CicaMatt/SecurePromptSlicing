import java.util.HashMap;
import java.util.Map;

public class Environment {
    private Map<String, String> requestParameters;
    private String template;

    public Environment(Map<String, String> requestParameters, String template) {
        this.requestParameters = requestParameters;
        this.template = template;
    }

    public String getRequestParameter(String key) {
        return requestParameters.get(key);
    }

    public String getTemplate() {
        return template;
    }
}

public class Renderer {

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequestParameter("name");
        String template = env.getTemplate();
        return template.replace("{name}", name);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, String> requestParameters = new HashMap<>();
        requestParameters.put("name", "John Doe");
        Environment env = new Environment(requestParameters, "Hello, {name}!");

        System.out.println(home(env));
    }
}