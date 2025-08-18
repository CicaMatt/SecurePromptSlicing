import java.util.HashMap;
import java.util.Map;

class Environment {
    private Map<String, String> templates = new HashMap<>();

    public void addTemplate(String name, String template) {
        templates.put(name, template);
    }

    public String getTemplate(String name) {
        return templates.getOrDefault(name, "");
    }

    public String getParameter(String param) {
        // For simplicity, we'll simulate getting a parameter
        if (param.equals("name")) {
            return "World";
        }
        return "";
    }
}

public class Renderer {

    public static String render_response_from_env(Environment env) {
        String name = env.getParameter("name");
        String template = env.getTemplate("greeting");
        return template.replace("{name}", name);
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        env.addTemplate("greeting", "Hello, {name}!");
        System.out.println(home(env));
    }
}