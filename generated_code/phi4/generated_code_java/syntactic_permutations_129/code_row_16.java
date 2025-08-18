import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // Simulating a request and environment for demonstration purposes.
        HttpServletRequest request = new MockHttpServletRequest("homeTemplate");
        HttpServletResponse response = new MockHttpServletResponse();
        
        String result = home(request, response);
        System.out.println(result);
    }

    public static String home(HttpServletRequest request, HttpServletResponse response) {
        String env = "production"; // Simulating environment variable
        return renderResponseFromEnv(env, request, response);
    }

    public static String renderResponseFromEnv(String env, HttpServletRequest request, HttpServletResponse response) {
        Map<String, Object> templateData = new HashMap<>();
        String templateName = request.getParameter("name");

        if (templateName == null || templateName.isEmpty()) {
            templateName = "defaultTemplate";
        }
        
        templateData.put("content", renderTemplate(templateName));

        return generateResponse(response, templateData);
    }

    private static String renderTemplate(String templateName) {
        // This is a simple implementation. In a real scenario, you would fetch and process the template.
        return "Rendered content for: " + templateName;
    }

    private static String generateResponse(HttpServletResponse response, Map<String, Object> data) {
        StringBuilder responseBody = new StringBuilder();
        
        for (Map.Entry<String, Object> entry : data.entrySet()) {
            responseBody.append(entry.getKey()).append(": ").append(entry.getValue()).append("\n");
        }
        
        // Set response content type and write the content
        response.setContentType("text/plain");
        return responseBody.toString();
    }

    // Mock classes to simulate HttpServletRequest and HttpServletResponse for demonstration purposes.
    static class MockHttpServletRequest extends HttpServletRequestWrapper {
        private String name;

        public MockHttpServletRequest(String name) {
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

    static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private StringBuilder content;

        public MockHttpServletResponse() {
            this.content = new StringBuilder();
        }

        @Override
        public PrintWriter getWriter() throws IOException {
            return new PrintWriter(content);
        }

        @Override
        public void setContentLength(int len) {
            // No-op for demonstration purposes.
        }
    }
}