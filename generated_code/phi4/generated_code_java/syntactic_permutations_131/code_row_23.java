import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class WebServer {

    public static void main(String[] args) {
        // This is a placeholder for the server setup.
        // You would need to set up a servlet container or use a framework like Spring Boot
        // to properly run this application in a web environment.
    }

    public static String renderResponseFromEnv(HttpServletRequest request, Environment env) throws IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate();
        String renderedTemplate = template.render(name);
        return renderedTemplate;
    }

    public static class HomeServlet extends HttpServlet {
        private final Environment env;

        public HomeServlet(Environment env) {
            this.env = env;
        }

        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String content = renderResponseFromEnv(request, env);
            response.setContentType("text/html");
            response.getWriter().write(content);
        }
    }

    static class Environment {
        private final Template template;

        public Environment(Template template) {
            this.template = template;
        }

        public Template getTemplate() {
            return template;
        }
    }

    interface Template {
        String render(String name);
    }

    static class SimpleTemplate implements Template {
        @Override
        public String render(String name) {
            if (name == null || name.isEmpty()) {
                name = "World";
            }
            return "<html><body><h1>Hello, " + name + "!</h1></body></html>";
        }
    }
}