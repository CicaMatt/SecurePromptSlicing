import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    private final Map<String, String> userMappings = new HashMap<>();

    public void init() {
        // Initialize with some example usernames
        userMappings.put("alice", "Alice");
        userMappings.put("bob", "Bob");
        userMappings.put("charlie", "Charlie");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && !pathInfo.isEmpty()) {
            String usernameKey = pathInfo.substring(1); // remove the leading '/'
            String userName = userMappings.getOrDefault(usernameKey, "Unknown User");
            String message = hello(userName);
            response.setContentType("text/html");
            response.getWriter().write(message);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format. Expected /hello/username");
        }
    }

    private String hello(String username) {
        return escape("Hello " + username);
    }

    private String escape(String input) {
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    escaped.append("&lt;");
                    break;
                case '>':
                    escaped.append("&gt;");
                    break;
                case '&':
                    escaped.append("&amp;");
                    break;
                case '"':
                    escaped.append("&quot;");
                    break;
                case '\'':
                    escaped.append("&#39;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }
}