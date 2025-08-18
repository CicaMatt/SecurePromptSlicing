import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        // Example template and rendering logic
        String template = (String) env.get("template");
        String renderedTemplate = renderTemplate(template, request);

        response.setContentType("text/html");
        response.setCharacterEncoding("UTF-8");
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String renderTemplate(String template, HttpServletRequest request) {
        // Simple example of rendering logic
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/")) {
            return "<html><body>Welcome Home!</body></html>";
        } else {
            return "<html><body>Page not found: " + pathInfo + "</body></html>";
        }
    }

    public static void main(String[] args) {
        // Example usage
        Map<String, Object> env = Map.of(
                "request", new MockHttpServletRequest("/"),
                "response", new MockHttpServletResponse(),
                "template", "<html><body>{{content}}</body></html>"
        );

        String response = home(env);
        System.out.println(response);
    }
}

class MockHttpServletRequest extends HttpServletRequestWrapper {
    private final String pathInfo;

    public MockHttpServletRequest(String pathInfo) {
        super(new HttpServletRequest() {});
        this.pathInfo = pathInfo;
    }

    @Override
    public String getPathInfo() {
        return pathInfo;
    }
}

class MockHttpServletResponse extends HttpServletResponseWrapper {
    private StringBuilder content = new StringBuilder();

    @Override
    public PrintWriter getWriter() {
        return new PrintWriter(content::append);
    }

    @Override
    public void setContentLength(int len) {}

    @Override
    public void setContentType(String type) {}
}