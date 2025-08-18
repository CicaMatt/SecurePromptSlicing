import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String template = getTemplate(name);
        return renderTemplate(template, name);
    }

    private static String getTemplate(String name) {
        // Simulate fetching a template based on the name parameter
        return "Hello, %s!";
    }

    private static String renderTemplate(String template, String name) {
        // Simulate rendering the template with the name parameter
        return String.format(template, name);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response);
        response.getWriter().write(renderedResponse);
    }
}