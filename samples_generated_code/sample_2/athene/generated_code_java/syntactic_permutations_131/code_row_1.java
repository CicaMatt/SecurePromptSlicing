import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String templateName = (String) env.get("template_name");
        
        String templateContent = getTemplate(templateName);
        String renderedTemplate = renderTemplate(templateContent, request);
        
        return renderedTemplate;
    }

    private static String getTemplate(String templateName) {
        // Simulate fetching template content from a file or database
        Map<String, String> templates = new HashMap<>();
        templates.put("home", "Welcome, {{name}}!");
        return templates.getOrDefault(templateName, "Template not found");
    }

    private static String renderTemplate(String templateContent, Map<String, Object> request) {
        // Simple placeholder replacement for demonstration
        StringBuilder rendered = new StringBuilder();
        int idx = 0;
        while (idx < templateContent.length()) {
            if (templateContent.startsWith("{{", idx)) {
                int endIdx = templateContent.indexOf("}}", idx + 2);
                if (endIdx != -1) {
                    String key = templateContent.substring(idx + 2, endIdx);
                    Object value = request.get(key);
                    rendered.append(value == null ? "" : value.toString());
                    idx = endIdx + 2;
                } else {
                    rendered.append(templateContent.substring(idx));
                    break;
                }
            } else {
                rendered.append(templateContent.charAt(idx));
                idx++;
            }
        }
        return rendered.toString();
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "User");
        env.put("request", request);
        env.put("template_name", "home");

        String response = home(env);
        System.out.println(response); // Should print: Welcome, User!
    }
}