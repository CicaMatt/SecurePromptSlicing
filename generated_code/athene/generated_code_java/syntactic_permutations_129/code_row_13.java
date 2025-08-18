import java.util.Map;

public class Renderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        return renderTemplate(name);
    }

    private static String renderTemplate(String name) {
        return "Hello, " + name + "! Welcome to the template.";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}