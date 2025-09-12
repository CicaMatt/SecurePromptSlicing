import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // Example usage, in a real application this would be part of a web framework setup.
        HttpServletRequest request = createMockRequest("John Doe");
        HttpServletResponse response = new HttpServletResponse() {}; // Mock implementation
        String result = home(request, response);
        
        System.out.println(result); // Output the rendered template
    }

    public static String renderResponseFromEnv(HttpServletRequest request, Map<String, String> env) {
        String name = request.getParameter("name");

        if (env.containsKey(name)) {
            String template = env.get(name);

            return new StringBuilder(template)
                .replace("{name}", name)
                .toString();
        } else {
            return "Template not found.";
        }
    }

    public static String home(HttpServletRequest request, HttpServletResponse response) {
        Map<String, String> env = Map.of(
            "greeting", "Hello, {name}!"
        );

        return renderResponseFromEnv(request, env);
    }

    private static HttpServletRequest createMockRequest(String nameParam) {
        // Mock implementation of HttpServletRequest for demonstration purposes.
        return new HttpServletRequest() {
            @Override
            public String getParameter(String name) {
                if ("name".equals(name)) {
                    return nameParam;
                }
                return null;
            }

            // Implement other methods as no-op or default values
            @Override public String getContextPath() { return ""; }
            @Override public int getContentLength() { return 0; }
            @Override public String getMethod() { return "GET"; }
            @Override public javax.servlet.http.Cookie[] getCookies() { return new javax.servlet.http.Cookie[0]; }
            @Override public javax.servlet.ServletInputStream getInputStream() { throw new UnsupportedOperationException(); }
            @Override public java.net.URL getParameterRealUrlEncoded(String s) { throw new UnsupportedOperationException(); }
            @Override public String getProtocol() { return "HTTP/1.1"; }
            @Override public String getScheme() { return "http"; }
            @Override public String getRequestURI() { return ""; }
            @Override public StringBuffer getRequestURL() { return new StringBuffer(""); }
            @Override public javax.servlet.http.HttpServletResponse getResponse() { throw new UnsupportedOperationException(); }
            @Override public javax.servlet.ServletOutputStream getOutputStream() throws java.io.IOException { throw new UnsupportedOperationException(); }
            @Override public void setAttribute(String s, Object o) {}
            @Override public void addCookie(javax.servlet.http.Cookie cookie) {}
        };
    }

    // Mock HttpServletResponse for demonstration
    private static class HttpServletResponse {
        // Implement necessary methods as no-op or default values if needed.
    }
}