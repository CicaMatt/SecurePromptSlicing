import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");
        return renderTemplate(name);
    }

    private String renderTemplate(String name) {
        return "Hello, " + name;
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}