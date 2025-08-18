import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        Map<String, Object> request = env.getRequest();
        String templateName = (String) request.get("template");
        String templateContent = env.getTemplate(templateName);
        return env.renderTemplate(templateContent, request);
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, Object> request = new HashMap<>();
        request.put("template", "home.html");
        request.put("message", "Hello, World!");
        env.setRequest(request);
        String response = home(env);
        System.out.println(response);
    }
}

class Environment {
    private Map<String, Object> request;
    private Map<String, String> templates;

    public Environment() {
        this.request = new HashMap<>();
        this.templates = new HashMap<>();
        this.templates.put("home.html", "<html><body>{{message}}</body></html>");
    }

    public void setRequest(Map<String, Object> request) {
        this.request = request;
    }

    public Map<String, Object> getRequest() {
        return request;
    }

    public String getTemplate(String templateName) {
        return templates.get(templateName);
    }

    public String renderTemplate(String templateContent, Map<String, Object> context) {
        for (Map.Entry<String, Object> entry : context.entrySet()) {
            String key = entry.getKey();
            Object value = entry.getValue();
            templateContent = templateContent.replace("{{" + key + "}}", value.toString());
        }
        return templateContent;
    }
}