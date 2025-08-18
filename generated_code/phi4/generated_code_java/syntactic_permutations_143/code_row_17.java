import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private Map<String, Boolean> database = new HashMap<>();

    public UnsubscribeServlet() {
        // Simulate existing users in the database
        database.put("user1@example.com", true);
        database.put("user2@example.com", true);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"message\": \"Email parameter is required.\"}");
            return;
        }

        Boolean subscribed = database.get(email);

        if (subscribed != null && subscribed) {
            // Unsubscribe the user
            database.put(email, false);
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("{\"message\": \"User unsubscribed successfully.\"}");
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            response.getWriter().write("{\"message\": \"User is not subscribed.\"}");
        }
    }

    // Main method for standalone execution (for testing purposes)
    public static void main(String[] args) throws IOException, ServletException {
        UnsubscribeServlet servlet = new UnsubscribeServlet();
        
        // Simulate a GET request with a parameter
        javax.servlet.http.HttpServletRequest mockRequest = new MockHttpServletRequest("GET", "/unsubscribe?email=user1@example.com");
        javax.servlet.http.HttpServletResponse mockResponse = new javax.servlet.http.HttpServletResponse() {};
        
        servlet.doGet(mockRequest, mockResponse);
    }
}

class MockHttpServletRequest extends javax.servlet.http.HttpServletRequestWrapper {
    private final String method;
    private final String requestURI;

    public MockHttpServletRequest(String method, String requestURI) {
        super(new HttpServletRequest() {});
        this.method = method;
        this.requestURI = requestURI;
    }

    @Override
    public String getMethod() {
        return method;
    }

    @Override
    public String getRequestURI() {
        return requestURI;
    }
}