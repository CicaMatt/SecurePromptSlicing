import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        // Simulate getting the name parameter from the user request
        String name = (String) env.get("name");
        
        // Render with the name parameter from the request
        String renderedTemplate = "Hello, " + name + "!";
        
        // Return a response with the rendered template
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        // Call the render_response_from_env function with the env variable
        String response = render_response_from_env(env);
        
        // Return the response from the render_response_from_env
        return response;
    }

    public static void main(String[] args) {
        // Simulate an environment map with a name parameter
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        
        // Call the home function and print the response
        String response = home(env);
        System.out.println(response);
    }
}