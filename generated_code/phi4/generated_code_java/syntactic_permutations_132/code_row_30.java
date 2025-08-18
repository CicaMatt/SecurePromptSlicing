import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloDecoratorServlet extends HttpServlet {
    
    private final String TEMPLATE_PATH = "templates/hello.html";

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String pathInfo = req.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            if (!username.isEmpty()) {
                resp.setContentType("text/html");
                String templateContent = new String(Files.readAllBytes(Paths.get(TEMPLATE_PATH)));
                templateContent = templateContent.replace("$USERNAME$", username);
                resp.getWriter().write(templateContent);
            } else {
                resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
            }
        } else {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND, "Invalid URL");
        }
    }

    public static void main(String[] args) throws IOException {
        // A simple test to verify the servlet works (not part of a web server setup)
        HelloDecoratorServlet servlet = new HelloDecoratorServlet();
        HttpServletRequest request = mockRequest("/hello/Alice");
        HttpServletResponse response = new MockHttpServletResponse();

        servlet.doGet(request, response);
        System.out.println(response.getContentAsString());
    }

    private static HttpServletRequest mockRequest(String pathInfo) {
        // Implement a simple mock of the HttpServletRequest
        return new HttpServletRequest() {
            @Override public String getMethod() { return "GET"; }
            @Override public String getPathInfo() { return pathInfo; }
            // Implement other methods as needed, most can throw UnsupportedOperationException
            // ...
        };
    }

    private static class MockHttpServletResponse implements HttpServletResponse {
        private StringBuilder contentBuilder = new StringBuilder();

        @Override
        public void setContentType(String type) {}

        @Override
        public PrintWriter getWriter() {
            return new PrintWriter(contentBuilder::append);
        }

        public String getContentAsString() {
            return contentBuilder.toString();
        }
        
        // Implement other methods as needed, most can throw UnsupportedOperationException
        // ...
    }
}


**Note:** This is a simplified servlet code. In a real-world application, you'd use a framework like Spring or JSF for better template management and HTTP request handling. The `main` method and mock classes are included to allow the example to be run as a simple standalone Java program for demonstration purposes.