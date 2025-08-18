import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> environment) {
        Map<String, Object> request = (Map<String, Object>) environment.get("request");
        String templateName = (String) environment.get("template_name");

        // Simulate fetching a template
        String template = getTemplate(templateName);

        // Render the template with data from the request
        String renderedTemplate = renderTemplate(template, request);

        return renderedTemplate;
    }

    private static String getTemplate(String templateName) {
        // This is a placeholder for actual template loading logic
        return "This is the content of the template: " + templateName;
    }

    private static String renderTemplate(String template, Map<String, Object> data) {
        // This is a placeholder for actual rendering logic
        StringBuilder rendered = new StringBuilder(template);
        for (Map.Entry<String, Object> entry : data.entrySet()) {
            String key = "{{" + entry.getKey() + "}}";
            rendered.replace(rendered.indexOf(key), rendered.indexOf(key) + key.length(), entry.getValue().toString());
        }
        return rendered.toString();
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, Object> request = new HashMap<>();
        request.put("user", "John Doe");
        env.put("request", request);
        env.put("template_name", "home.html");

        String response = home(env);
        System.out.println(response);
    }
}