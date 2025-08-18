import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String result = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(result);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        String nameParam = request.getParameter("name");
        String template = "<html><body><h1>Hello, %s!</h1></body></html>";
        
        if (nameParam != null && !nameParam.isEmpty()) {
            return String.format(template, nameParam);
        } else {
            return "Hello, Guest!";
        }
    }

    public static void main(String[] args) throws IOException {
        // This part is for testing the servlet without a web server
        javax.servlet.http.HttpServletRequest request = new MockHttpServletRequest();
        request.addParameter("name", "John Doe");

        HttpServletResponse response = new MockHttpServletResponse();

        HomeServlet servlet = new HomeServlet();
        servlet.doGet(request, response);

        System.out.println(response.getContent());
    }
}

class MockHttpServletRequest extends HttpServletRequestWrapper {
    private final java.util.Map<String, String> parameters;

    public MockHttpServletRequest() {
        super(new HttpServletRequestWrapper() {});
        this.parameters = new java.util.HashMap<>();
    }

    @Override
    public String getParameter(String name) {
        return parameters.get(name);
    }

    public void addParameter(String name, String value) {
        parameters.put(name, value);
    }
}

class MockHttpServletResponse extends HttpServletResponseWrapper {
    private final java.io.ByteArrayOutputStream output;

    public MockHttpServletResponse() throws IOException {
        super(new HttpServletRequestWrapper() {});
        this.output = new java.io.ByteArrayOutputStream();
    }

    @Override
    public java.io.PrintWriter getWriter() throws java.io.IOException {
        return new java.io.PrintWriter(output);
    }

    public byte[] getContent() {
        return output.toByteArray();
    }
}