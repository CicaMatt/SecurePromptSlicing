import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class RenderResponseFromEnv {

    public static void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String template = getTemplateFromEnvironment(request);

        if (template == null || template.isEmpty()) {
            template = "Default Template: Hello, %s!";
        }

        String renderedContent = String.format(template, name != null ? name : "Guest");

        response.setContentType("text/html");
        response.getWriter().write(renderedContent);
    }

    private static String getTemplateFromEnvironment(HttpServletRequest request) {
        // Simulate getting a template from the environment
        // In practice, this could be loaded from a resource bundle or configuration file.
        return (String) request.getAttribute("template");
    }

    public static void main(String[] args) {
        // This is just for demonstration purposes and won't run in a standalone Java application.
        // Normally, you would deploy this as part of a web application with a servlet container like Tomcat or Jetty.
    }
}