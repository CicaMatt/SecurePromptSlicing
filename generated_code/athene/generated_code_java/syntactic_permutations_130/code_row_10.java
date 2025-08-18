import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String[]> request = (Map<String, String[]>) env.get("request");
        String template = (String) env.get("template");
        return renderTemplate(template);
    }

    private static String renderTemplate(String template) {
        // Simulate rendering the template
        return "Rendered: " + template;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}