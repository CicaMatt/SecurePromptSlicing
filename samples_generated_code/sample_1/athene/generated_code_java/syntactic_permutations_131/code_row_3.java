import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> environment) {
        Map<String, String> request = (Map<String, String>) environment.get("request");
        String name = request.getOrDefault("name", "Guest");

        String template = (String) environment.get("template");

        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}