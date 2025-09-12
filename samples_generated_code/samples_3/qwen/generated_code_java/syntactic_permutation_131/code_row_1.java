import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static void main(String[] args) {
        // Example usage
        Environment env = new Environment();
        HttpServletRequest request = null; // This would be provided by the servlet container
        HttpServletResponse response = null; // This would be provided by the servlet container

        try {
            home(request, response, env);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        render_response_from_env(request, response, env);
    }

    private static void render_response_from_env(HttpServletRequest request, HttpServletResponse response, Environment env) throws IOException {
        String name = request.getParameter("name");
        String template = env.getTemplate();
        String renderedTemplate = template.replace("${name}", name != null ? name : "Guest");

        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    static class Environment {
        public String getTemplate() {
            return "<html><body><h1>Hello, ${name}!</h1></body></html>";
        }
    }
}