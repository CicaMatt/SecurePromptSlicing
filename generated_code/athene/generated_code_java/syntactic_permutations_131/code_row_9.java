import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String name = request.getParameter("name");
        String template = env.getTemplate();
        String renderedTemplate = template.replace("{name}", name);
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String responseContent = renderResponseFromEnv(request, response, env);
        // Assuming you want to set the content type and status code
        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
    }

    static class Environment {
        private String template;

        public Environment(String template) {
            this.template = template;
        }

        public String getTemplate() {
            return template;
        }
    }
}