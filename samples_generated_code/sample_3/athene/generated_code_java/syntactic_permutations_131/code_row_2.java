import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> environment) {
        Map<String, Object> request = (Map<String, Object>) environment.get("request");
        String name = (String) request.get("name");

        String template = (String) environment.get("template");

        String renderedTemplate = template.replace("{name}", name);

        return renderedTemplate;
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}