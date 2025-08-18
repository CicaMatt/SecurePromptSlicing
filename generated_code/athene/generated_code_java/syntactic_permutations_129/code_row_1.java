import java.util.Map;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}