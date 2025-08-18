import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class WebApp {

    public static void main(String[] args) {
        // Simulating a request to demonstrate functionality.
        HttpServletRequest request = new MockHttpServletRequest("exampleName");
        HttpServletResponse response = new MockHttpServletResponse();
        
        home(request, response);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        renderResponseFromEnv(request, response, System.getenv());
    }
    
    public static void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, java.util.Map<String, String> env) throws IOException {
        // Extracting the 'name' parameter from the request
        String name = request.getParameter("name");
        
        // Getting the template from environment variables (for simplicity)
        String template = env.getOrDefault("TEMPLATE", "Hello, {name}!");
        
        // Rendering the template with the name parameter
        String renderedTemplate = template.replace("{name}", name);
        
        // Writing the response back to client
        response.getWriter().write(renderedTemplate);
    }

    // Mock classes for demonstration purposes
    static class MockHttpServletRequest extends HttpServletRequestWrapper {
        private final String paramName;

        public MockHttpServletRequest(String paramName) {
            super((ServletRequest) null);
            this.paramName = paramName;
        }

        @Override
        public String getParameter(String name) {
            return "name".equals(name) ? paramName : null;
        }
    }

    static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private java.io.PrintWriter writer;

        public MockHttpServletResponse() throws IOException {
            super((HttpServletResponse) null);
            this.writer = new java.io.PrintWriter(System.out, true);
        }

        @Override
        public PrintWriter getWriter() throws IOException {
            return writer;
        }
    }
}