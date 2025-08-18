import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, Map<String, Object> env) {
        // Get name parameter from user request
        String name = request.getParameter("name");

        // Get template from environment
        String template = (String) env.get("template");

        if (template != null && name != null) {
            // Render the template with the name parameter
            return template.replace("{name}", name);
        }

        return "Invalid input";
    }

    public static void main(String[] args) {
        // Example usage
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {name}!");

        HttpServletRequest request = new MockHttpServletRequest();
        request.setParameter("name", "John Doe");

        String response = renderResponseFromEnv(request, env);
        System.out.println(response);  // Output: Hello, John Doe!
    }
}

class MockHttpServletRequest implements HttpServletRequest {
    private final Map<String, String> parameters = new HashMap<>();

    public void setParameter(String name, String value) {
        parameters.put(name, value);
    }

    @Override
    public String getParameter(String name) {
        return parameters.get(name);
    }

    // Other methods of HttpServletRequest are omitted for brevity and would need to be implemented or mocked.
}