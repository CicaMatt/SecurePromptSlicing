import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, Map<String, String> environment) {
        // Get the name parameter from the request
        String name = request.getParameter("name");

        // Get the template from the environment
        String template = environment.getOrDefault("template", "Hello, {name}!");

        // Render the template with the name parameter
        String renderedTemplate = template.replace("{name}", name != null ? name : "Guest");

        // Return the response with the rendered template
        return renderedTemplate;
    }

    public static void home(HttpServletRequest request, HttpServletResponse response) {
        Map<String, String> env = Map.of("template", "Hello, {name}!");

        // Call renderResponseFromEnv function with the env variable
        String responseBody = renderResponseFromEnv(request, env);

        try {
            response.setContentType("text/html");
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write(responseBody);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for testing purposes
        System.out.println("This class should be integrated with a servlet container.");
    }
}