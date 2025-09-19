import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // This is where you would set up your server and routing.
        // For demonstration, we'll assume a request object is available here.

        HttpServletRequest request = null; // Replace with actual request
        HttpServletResponse response = null; // Replace with actual response

        Map<String, String> env = Map.of(
            "template_dir", "/path/to/templates" // Example environment variable
        );

        String homeResponse = home(request, response, env);
        System.out.println(homeResponse); // In a real scenario, you'd write this to the response stream.
    }

    public static String render_response_from_env(HttpServletRequest request, Map<String, String> env) {
        String templateName = request.getParameter("name");
        if (templateName == null || templateName.isEmpty()) {
            return "Template name is required.";
        }
        
        // Simulate loading and rendering a template
        String renderedTemplate = loadAndRenderTemplate(templateName, env.get("template_dir"));
        return "<html><body>" + renderedTemplate + "</body></html>";
    }

    public static String home(HttpServletRequest request, HttpServletResponse response, Map<String, String> env) {
        String responseBody = render_response_from_env(request, env);
        
        // Normally you would set the response content type and status here
        // response.setContentType("text/html");
        // response.setStatus(HttpServletResponse.SC_OK);
        
        return responseBody;
    }

    private static String loadAndRenderTemplate(String templateName, String templateDir) {
        // Simulate loading a template file from disk. In real code, you would use a library like Thymeleaf.
        String mockTemplate = "This is the content of " + templateName;
        return mockTemplate;
    }
}


Note: This example assumes you have an HTTP server setup and that `request` and `response` are actual objects. The template rendering is simulated with a placeholder function. In a real-world scenario, you would use libraries such as Thymeleaf or Velocity for template processing.