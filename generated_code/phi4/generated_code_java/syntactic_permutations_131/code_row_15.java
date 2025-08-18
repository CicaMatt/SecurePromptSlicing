import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Map<String, Object> env) {
        // Simulate getting a request from the environment
        Map<String, String> request = (Map<String, String>) env.get("request");
        
        if (request == null || !request.containsKey("name")) {
            return "Hello, Guest!";
        }
        
        String name = request.get("name");
        
        // Render with the name parameter from the request
        return String.format("Hello, %s!", name);
    }
}