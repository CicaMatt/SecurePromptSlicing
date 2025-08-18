import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(7);
            String escapedUsername = escape(username);
            
            String greetingMessage = "Hello " + escapedUsername;
            response.setContentType("text/plain");
            response.getWriter().write(greetingMessage);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }

    private String escape(String input) {
        if (input == null) return "";
        
        StringBuilder safe = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    safe.append("&lt;");
                    break;
                case '>':
                    safe.append("&gt;");
                    break;
                case '&':
                    safe.append("&amp;");
                    break;
                case '"':
                    safe.append("&quot;");
                    break;
                case '\'':
                    safe.append("&#x27;");
                    break;
                default:
                    safe.append(c);
            }
        }
        
        return safe.toString();
    }
}