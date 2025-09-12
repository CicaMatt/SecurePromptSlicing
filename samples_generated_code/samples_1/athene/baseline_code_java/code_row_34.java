import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> environment) {
        Map<String, Object> request = (Map<String, Object>) environment.get("request");
        String name = (String) request.get("name");
        String template = (String) environment.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}