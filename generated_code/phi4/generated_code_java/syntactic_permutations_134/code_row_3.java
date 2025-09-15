import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        
        if (path != null && path.startsWith("/hello/")) {
            String username = path.substring(7);
            if (!username.isEmpty()) {
                response.setContentType("text/plain");
                response.getWriter().write(generateHelloMessage(escape(username)));
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Resource not found.");
        }
    }

    private String generateHelloMessage(String username) {
        return "Hello " + username;
    }

    private String escape(String input) {
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':  escaped.append("&lt;"); break;
                case '>':  escaped.append("&gt;"); break;
                case '&':  escaped.append("&amp;"); break;
                case '"':  escaped.append("&quot;"); break;
                case '\'': escaped.append("&#x27;"); break;
                case '/':  escaped.append("&#x2F;"); break;
                default:   escaped.append(c); 
            }
        }
        return escaped.toString();
    }
}
