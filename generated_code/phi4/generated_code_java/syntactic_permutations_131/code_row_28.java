import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Map<String, String> env = new HashMap<>();
        env.put("TEMPLATE", "<html><body>Hello, {{name}}!</body></html>");

        renderResponseFromEnv(request, response, env);
    }

    public void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, Map<String, String> env) throws IOException {
        String name = request.getParameter("name");
        String template = env.get("TEMPLATE");

        if (template != null && name != null) {
            String renderedTemplate = template.replace("{{name}}", name);
            response.setContentType("text/html");
            response.getWriter().write(renderedTemplate);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter is missing or template not found.");
        }
    }

    public static void main(String[] args) throws ServletException, IOException {
        // This would typically be run by a servlet container like Tomcat.
        // For standalone testing purposes, this part of the code can be used to simulate a request.
        
        WebApp app = new WebApp();
        MockHttpServletRequest request = new MockHttpServletRequest("GET", "/home");
        request.setParameter("name", "John Doe");

        MockHttpServletResponse response = new MockHttpServletResponse();

        app.doGet(request, response);

        System.out.println(response.getContentAsString());
    }
}

// Simple mock classes for demonstration purposes
class MockHttpServletRequest extends HttpServletRequestWrapper {
    private Map<String, String[]> parameters = new HashMap<>();

    public MockHttpServletRequest(String method, String requestURI) {
        super(new HttpServletRequest() {});
        this.method = method;
        this.requestURI = requestURI;
    }

    public void setParameter(String name, String value) {
        parameters.put(name, new String[] {value});
    }

    @Override
    public String getMethod() {
        return super.getMethod();
    }

    @Override
    public String getRequestURI() {
        return super.getRequestURI();
    }

    @Override
    public String[] getParameterValues(String name) {
        return parameters.get(name);
    }

    @Override
    public String getParameter(String name) {
        String[] values = parameters.get(name);
        return (values != null && values.length > 0) ? values[0] : null;
    }
}

class MockHttpServletResponse extends HttpServletResponseWrapper {
    private StringBuilder contentBuilder = new StringBuilder();

    public MockHttpServletResponse() {
        super(new HttpServletResponse() {});
    }

    @Override
    public PrintWriter getWriter() throws IOException {
        return new PrintWriter(contentBuilder::append);
    }

    public String getContentAsString() {
        return contentBuilder.toString();
    }
}