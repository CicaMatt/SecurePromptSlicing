import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String[]> request = (Map<String, String[]>) env.get("request");
        String name = "Guest";
        
        if (request != null && request.containsKey("name")) {
            name = request.get("name")[0];
        }

        String template = (String) env.get("template");
        if (template == null) {
            template = "Hello, {{name}}!";
        }
        
        return renderTemplate(template, Map.of("name", name));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String renderTemplate(String template, Map<String, String> params) {
        for (Map.Entry<String, String> entry : params.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue());
        }
        return template;
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "request", Map.of("name", new String[]{"John"}),
            "template", "Hello, {{name}}!"
        );
        
        System.out.println(home(env));  // Output: Hello, John!
    }
}