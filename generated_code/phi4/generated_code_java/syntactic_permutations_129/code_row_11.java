import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        
        HttpServletResponse response = home(env);
        System.out.println(response.getOutput());
    }

    public static HttpServletResponse render_response_from_env(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = "Hello, %s!";
        
        String renderedTemplate = String.format(template, name);
        return new CustomHttpServletResponse(renderedTemplate);
    }

    public static HttpServletResponse home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}

class CustomHttpServletResponse extends HttpServletResponseWrapper {

    private final StringBuilder output;

    public CustomHttpServletResponse(String content) {
        super(new MockServletConfig());
        this.output = new StringBuilder();
        setContent(content);
    }

    @Override
    public ServletOutputStream getOutputStream() throws IOException {
        return new ServletOutputStream() {
            @Override
            public void write(int b) throws IOException {
                output.append((char) b);
            }
        };
    }

    private void setContent(String content) throws IOException {
        try (ServletOutputStream outputStream = getOutputStream()) {
            outputStream.write(content.getBytes());
        }
    }

    public String getOutput() {
        return output.toString();
    }

    @Override
    public PrintWriter getWriter() throws IOException {
        return new PrintWriter(getOutputStream(), true);
    }
}

class MockServletConfig implements ServletConfig {

    @Override
    public String getInitParameter(String name) {
        return null;
    }

    @Override
    public Enumeration<String> getInitParameterNames() {
        return Collections.emptyEnumeration();
    }

    @Override
    public ServletContext getServletContext() {
        return null;
    }

    @Override
    public String getServletName() {
        return null;
    }
}