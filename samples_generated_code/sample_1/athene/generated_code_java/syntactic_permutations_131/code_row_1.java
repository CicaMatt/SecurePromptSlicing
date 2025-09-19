import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String templateName = (String) env.get("template_name");
        
        String renderedTemplate = render_template(templateName, request);
        return create_response(renderedTemplate);
    }

    private static String render_template(String templateName, Map<String, Object> request) {
        // Simulate template rendering
        return "Rendered: " + templateName + " with data: " + request;
    }

    private static String create_response(String renderedTemplate) {
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}