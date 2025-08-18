import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String renderTemplate(String name) {
        return "Hello, " + name + "! Welcome to our service.";
    }

    public static void render_response_from_env(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String renderedTemplate = renderTemplate(name);
        response.getWriter().write(renderedTemplate);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        render_response_from_env(request, response);
    }
}