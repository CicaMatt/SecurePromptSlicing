import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }

    public static void main(String[] args) throws Exception {
        // Create a mock servlet environment for testing purposes
        MockHttpServletRequest req = new MockHttpServletRequest();
        req.setParameter("username", "JohnDoe");

        MockHttpServletResponse res = new MockHttpServletResponse();

        HelloServlet servlet = new HelloServlet();
        ServletConfig config = new SimpleServletConfig(servlet);
        
        servlet.init(config);

        servlet.doGet(req, res);

        System.out.println(res.getOutput());
    }
}

class MockHttpServletRequest extends HttpServletRequestWrapper {
    private final java.util.Map<String, String[]> parameters;

    public MockHttpServletRequest() {
        super(new HttpServletRequestWrapper(null));
        this.parameters = new java.util.HashMap<>();
    }

    @Override
    public String getParameter(String name) {
        return parameters.get(name)[0];
    }

    public void setParameter(String name, String value) {
        parameters.put(name, new String[]{value});
    }
}

class MockHttpServletResponse extends HttpServletResponseWrapper {
    private final ByteArrayOutputStream output = new ByteArrayOutputStream();
    private PrintWriter writer;

    @Override
    public ServletOutputStream getOutputStream() throws IOException {
        throw new UnsupportedOperationException("Use getWriter()");
    }

    @Override
    public PrintWriter getWriter() throws IOException {
        if (writer == null) {
            writer = new PrintWriter(output);
        }
        return writer;
    }

    public String getOutput() {
        return output.toString();
    }
}

class SimpleServletConfig implements ServletConfig {
    private final Servlet servlet;

    public SimpleServletConfig(Servlet servlet) {
        this.servlet = servlet;
    }

    @Override
    public String getInitParameter(String name) {
        throw new UnsupportedOperationException("Not supported.");
    }

    @Override
    public Enumeration<String> getInitParameterNames() {
        throw new UnsupportedOperationException("Not supported.");
    }

    @Override
    public ServletContext getServletContext() {
        return null;
    }

    @Override
    public String getServletName() {
        return servlet.getClass().getName();
    }
}