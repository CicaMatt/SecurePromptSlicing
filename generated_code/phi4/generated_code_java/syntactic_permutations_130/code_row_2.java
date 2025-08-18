import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static String renderResponseFromEnv(HttpServletRequest request, String template) {
        String name = request.getParameter("name");
        return template.replace("{name}", name != null ? name : "Guest");
    }

    public static String home(HttpServletRequest request) {
        Map<String, Object> env = (Map<String, Object>) request.getAttribute("env");
        String template = (String) env.get("template");
        return renderResponseFromEnv(request, template);
    }

    public static void main(String[] args) {
        // This is a placeholder for the actual web server setup
        HttpServletRequest mockRequest = new MockHttpServletRequest();
        HttpServletResponse mockResponse = new MockHttpServletResponse();

        mockRequest.setParameter("name", "John Doe");
        Map<String, Object> env = Map.of("template", "<h1>Hello, {name}!</h1>");
        mockRequest.setAttribute("env", env);

        String responseContent = home(mockRequest);
        mockResponse.getWriter().write(responseContent);

        System.out.println(mockResponse.getContentAsString());
    }

    // Mock classes for demonstration purposes
    static class MockHttpServletRequest extends HttpServletRequestWrapper {
        private Map<String, String> parameters;

        public MockHttpServletRequest() {
            this.parameters = Map.of();
        }

        @Override
        public String getParameter(String name) {
            return parameters.get(name);
        }

        public void setParameter(String name, String value) {
            parameters.put(name, value);
        }
    }

    static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private java.io.ByteArrayOutputStream output = new java.io.ByteArrayOutputStream();

        @Override
        public PrintWriter getWriter() {
            return new PrintWriter(output);
        }

        public String getContentAsString() {
            return output.toString();
        }
    }
}