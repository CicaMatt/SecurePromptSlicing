import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("REQUEST_PARAMETER_NAME");
        String template = (String) env.get("TEMPLATE");

        return "Hello, " + name + "! " + template;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("REQUEST_PARAMETER_NAME", "World");
        env.put("TEMPLATE", "Welcome to our website!");

        String response = home(env);
        System.out.println(response);
    }
}