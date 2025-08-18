import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String templateName = (String) env.get("template_name");
        String renderedTemplate = renderTemplate(templateName, request);
        return createResponse(renderedTemplate);
    }

    private String renderTemplate(String templateName, Map<String, Object> data) {
        // Simulate template rendering
        return "Rendered: " + templateName + " with data: " + data;
    }

    private String createResponse(String renderedTemplate) {
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + renderedTemplate;
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}