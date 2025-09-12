import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> environment = Map.of(
            "TEMPLATE", "<h1>Hello, {{name}}!</h1>"
        );
        
        System.out.println(home(environment));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> environment) {
        String template = environment.get("TEMPLATE");
        if (template == null) {
            throw new IllegalStateException("Template not found in the environment.");
        }
        
        // Simulating a request object with a name parameter
        Map<String, String> requestParams = Map.of("name", "World");

        return renderTemplate(template, requestParams);
    }

    public static String renderTemplate(String template, Map<String, String> params) {
        for (Map.Entry<String, String> param : params.entrySet()) {
            template = template.replace("{{" + param.getKey() + "}}", param.getValue());
        }
        return template;
    }
}