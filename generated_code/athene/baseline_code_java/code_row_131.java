import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> parameters = (Map<String, String[]>) env.get("parameters");
        String name = parameters.get("name") != null ? parameters.get("name")[0] : "World";
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}