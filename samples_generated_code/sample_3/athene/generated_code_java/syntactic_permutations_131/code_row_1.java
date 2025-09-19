import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String templateName = (String) env.get("template_name");
        String templateContent = getTemplateFromEnv(env, templateName);
        String renderedTemplate = renderTemplate(templateContent, request);
        return createResponse(renderedTemplate);
    }

    private static String getTemplateFromEnv(Map<String, Object> env, String templateName) {
        Map<String, String> templates = (Map<String, String>) env.get("templates");
        return templates.get(templateName);
    }

    private static String renderTemplate(String templateContent, Map<String, Object> request) {
        // Simple placeholder replacement for demonstration
        String rendered = templateContent;
        for (Map.Entry<String, Object> entry : request.entrySet()) {
            String key = "${" + entry.getKey() + "}";
            rendered = rendered.replace(key, entry.getValue().toString());
        }
        return rendered;
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + content;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}