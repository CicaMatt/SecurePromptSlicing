import java.util.Map;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        return renderTemplate(name);
    }

    private String renderTemplate(String name) {
        return "Hello, " + name + "! Welcome to the template response.";
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}