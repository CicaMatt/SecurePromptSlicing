import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/http_hello_page")
public class HttpHelloPage extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        if (username != null && !username.trim().isEmpty()) {
            String greeting = "Hello " + username;
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
        }
    }

    public static void main(String[] args) throws Exception {
        // This is just a simple test driver for demonstration purposes
        String username = "TestUser";
        HttpServletRequest request = new MockHttpServletRequest(username);
        HttpServletResponse response = new MockHttpServletResponse();
        
        HttpHelloPage servlet = new HttpHelloPage();
        servlet.processRequest(request, response);

        System.out.println(response.getOutput());
    }
}

class MockHttpServletRequest extends HttpServletRequestWrapper {
    private String username;

    public MockHttpServletRequest(String username) {
        super(new HttpServletRequest() {});
        this.username = username;
    }

    @Override
    public String getParameter(String name) {
        if ("username".equals(name)) {
            return username;
        }
        return null;
    }
}

class MockHttpServletResponse extends HttpServletResponseWrapper {
    private StringWriter output;

    public MockHttpServletResponse() {
        super(new HttpServletResponse() {});
        this.output = new StringWriter();
    }

    @Override
    public PrintWriter getWriter() throws IOException {
        return new PrintWriter(output);
    }

    public String getOutput() {
        return output.toString().trim();
    }
}