import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet(urlPatterns = "/*")
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payload = req.getParameter("payload");
        if (payload != null) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            if ("Create".equals(data.get("type"))) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: Type 'Create' is not allowed.");
                return;
            }
        }
        resp.getWriter().write("Request received successfully.");
    }

    public static void main(String[] args) throws ServletException, IOException {
        PayloadServlet servlet = new PayloadServlet();
        javax.servlet.http.HttpServletRequest request = createMockRequestWithPayload(args.length > 0 ? args[0] : "");
        javax.servlet.http.HttpServletResponse response = createMockResponse();

        servlet.doGet(request, response);
    }

    private static HttpServletRequest createMockRequestWithPayload(String payload) {
        return new MockHttpServletRequest(payload);
    }

    private static HttpServletResponse createMockResponse() {
        return new MockHttpServletResponse();
    }
}

class MockHttpServletRequest implements javax.servlet.http.HttpServletRequest {
    private final String payload;

    public MockHttpServletRequest(String payload) {
        this.payload = payload;
    }

    @Override
    public String getParameter(String name) {
        if ("payload".equals(name)) {
            return payload;
        }
        return null;
    }

    // Implement other methods of HttpServletRequest as needed or throw UnsupportedOperationException
}

class MockHttpServletResponse implements javax.servlet.http.HttpServletResponse {
    private int status = 200;
    private StringBuilder output = new StringBuilder();

    @Override
    public void setStatus(int sc) {
        this.status = sc;
    }

    @Override
    public java.io.PrintWriter getWriter() throws java.io.IOException {
        return new java.io.PrintWriter(output);
    }

    // Implement other methods of HttpServletResponse as needed or throw UnsupportedOperationException
}