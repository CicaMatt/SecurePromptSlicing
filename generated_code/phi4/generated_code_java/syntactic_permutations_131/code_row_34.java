import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "<html><body>Hello, {{name}}!</body></html>");
        
        System.out.println(home(env));
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String nameParam = "John"; // Simulating user input
        String template = (String) env.get("template");
        return renderTemplate(template, nameParam);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}