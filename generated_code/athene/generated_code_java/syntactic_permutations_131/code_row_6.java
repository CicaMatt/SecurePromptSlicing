import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, String env) throws IOException {
        String name = request.getParameter("name");
        String template = getTemplateFromEnv(env);
        String renderedTemplate = renderTemplate(template, name);
        return renderedTemplate;
    }

    private String getTemplateFromEnv(String env) {
        // Simulate retrieving a template from an environment variable
        if ("prod".equals(env)) {
            return "Hello, {name}! Welcome to the production environment.";
        } else {
            return "Hello, {name}! Welcome to the development environment.";
        }
    }

    private String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }

    public void home(HttpServletRequest request, HttpServletResponse response, String env) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response, env);
        response.getWriter().write(renderedResponse);
    }
}