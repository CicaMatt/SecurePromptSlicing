import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static void main(String[] args) {
        // Example usage, normally this would be part of a web framework setup.
        HttpServletRequest request = new MockHttpServletRequest("John Doe");
        HttpServletResponse response = new MockHttpServletResponse();
        
        String homeResponse = home(request, response);
        System.out.println(homeResponse.getContent());
    }

    public static class MockHttpServletRequest extends HttpServletRequestWrapper {
        private final String name;

        public MockHttpServletRequest(String name) {
            super((HttpServletRequest) null);
            this.name = name;
        }

        @Override
        public String getParameter(String name) {
            if ("name".equals(name)) {
                return this.name;
            }
            return null;
        }
    }

    public static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private StringBuilder content = new StringBuilder();

        @Override
        public PrintWriter getWriter() throws java.io.IOException {
            return new PrintWriter(content::append);
        }

        public String getContent() {
            return content.toString();
        }
    }

    public static String render_response_from_env(HashMap<String, String> env, HttpServletRequest request) {
        String template = env.getOrDefault("template", "Hello, {{name}}!");
        String name = request.getParameter("name");
        return template.replace("{{name}}", name);
    }

    public static String home(HttpServletRequest request, HttpServletResponse response) {
        HashMap<String, String> env = new HashMap<>();
        env.put("template", "Welcome to our site, {{name}}!");

        String renderedTemplate = render_response_from_env(env, request);

        try (PrintWriter out = response.getWriter()) {
            out.write(renderedTemplate);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return renderedTemplate;
    }
}
