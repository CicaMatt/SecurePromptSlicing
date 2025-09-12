import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        home(env);
    }

    public static void home(Map<String, String> env) {
        System.out.println(renderResponseFromEnv(env));
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String template = env.getOrDefault("template", "Hello, World!");
        String nameParam = getRequestParam("name");
        
        return template.replace("{{name}}", nameParam);
    }

    public static String getRequestParam(String param) {
        // Simulated user request parameters
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "John Doe");

        return requestParams.getOrDefault(param, "");
    }
}