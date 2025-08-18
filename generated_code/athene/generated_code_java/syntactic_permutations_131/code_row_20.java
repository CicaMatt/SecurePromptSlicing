import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}