import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        Map<String, Object> parameters = env.getRequestParameters();
        String name = (String) parameters.get("name");
        
        String template = env.getTemplate();
        
        return renderTemplate(template, name);
    }

    private static String renderTemplate(String template, String name) {
        // Simple placeholder for rendering logic
        return template.replace("${name}", name);
    }
}

class Environment {
    private final Map<String, Object> requestParameters;
    private final String template;

    public Environment(Map<String, Object> requestParameters, String template) {
        this.requestParameters = requestParameters;
        this.template = template;
    }

    public Map<String, Object> getRequestParameters() {
        return requestParameters;
    }

    public String getTemplate() {
        return template;
    }
}

class Main {
    public static void main(String[] args) {
        Map<String, Object> params = new HashMap<>();
        params.put("name", "John Doe");
        
        Environment env = new Environment(params, "Hello, ${name}!");
        
        String response = TemplateRenderer.renderResponseFromEnv(env);
        System.out.println(response); // Output: Hello, John Doe!
    }
}