import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String[]> params = (Map<String, String[]>) env.get("parameters");
        String nameParam = null;
        
        if (params != null && params.containsKey("name")) {
            nameParam = params.get("name")[0];
        }

        String template = (String) env.get("template");

        return renderTemplate(template, "name", nameParam);
    }

    private static String renderTemplate(String template, String variableName, String value) {
        if (template == null || value == null) {
            return "";
        }
        
        return template.replace("${" + variableName + "}", value != null ? value : "");
    }

    public static void main(String[] args) {
        // Example usage
        Map<String, Object> env = Map.of(
                "parameters", Map.of("name", new String[]{"John Doe"}),
                "template", "Hello, ${name}!"
        );

        System.out.println(renderResponseFromEnv(env));
    }
}