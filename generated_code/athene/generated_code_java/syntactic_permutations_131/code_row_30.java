import java.util.Map;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> environment) {
        return renderResponseFromEnv(environment);
    }
}