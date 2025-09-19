import java.util.Map;

public class ResponseRenderer {

    public String render_response_from_env(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.getOrDefault("template", "Hello, {name}!");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}