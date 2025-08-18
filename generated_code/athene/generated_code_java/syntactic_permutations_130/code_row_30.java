import java.util.Map;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");
        
        String template = (String) env.get("template");
        
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}