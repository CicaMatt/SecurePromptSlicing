import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // Simulate an environment and request for demonstration purposes.
        Environment env = new Environment();
        HttpServletRequest request = new MockHttpServletRequest("GET", "/home");
        HttpServletResponse response = new MockHttpServletResponse();

        String result = home(env, request);
        System.out.println(result);  // Output the rendered template
    }

    public static String home(Environment env, HttpServletRequest request) {
        return renderResponseFromEnv(env, request);
    }

    public static String renderResponseFromEnv(Environment env, HttpServletRequest request) {
        String userRequest = request.getParameter("user");
        String templateName = env.getTemplate();
        TemplateEngine engine = new TemplateEngine();

        // Render the template with the user request
        String renderedTemplate = engine.render(templateName, Map.of("user", userRequest));

        // Return a response with the rendered template
        return "HTTP/1.1 200 OK\n" + renderedTemplate;
    }

    static class Environment {
        private String template;

        public Environment() {
            this.template = "welcome.html";
        }

        public String getTemplate() {
            return template;
        }
    }

    static class TemplateEngine {
        public String render(String templateName, Map<String, Object> data) {
            // Simulating template rendering
            if ("welcome.html".equals(templateName)) {
                return "<html><body>Welcome, " + data.get("user") + "</body></html>";
            }
            return "<html><body>Template not found</body></html>";
        }
    }

    static class MockHttpServletRequest extends HttpServletRequestWrapper {
        private String method;
        private String pathInfo;

        public MockHttpServletRequest(String method, String path) {
            super(new HttpServletRequest() {});
            this.method = method;
            this.pathInfo = path;
        }

        @Override
        public String getMethod() {
            return method;
        }

        @Override
        public String getPathInfo() {
            return pathInfo;
        }

        @Override
        public String getParameter(String name) {
            if ("user".equals(name)) {
                return "John Doe";
            }
            return null;
        }
    }

    static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private StringBuilder content = new StringBuilder();

        public MockHttpServletResponse() {
            super(new HttpServletResponse() {});
        }

        @Override
        public PrintWriter getWriter() throws IOException {
            return new PrintWriter(content);
        }

        public String getContent() {
            return content.toString();
        }
    }
}