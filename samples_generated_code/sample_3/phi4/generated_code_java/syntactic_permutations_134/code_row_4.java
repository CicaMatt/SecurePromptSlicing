import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String[] pathParts = request.getPathInfo().split("/");
        
        if (pathParts.length == 2 && "hello".equals(pathParts[0])) {
            String username = escape(pathParts[1]);
            String message = hello(username);
            response.setContentType("text/plain");
            response.getWriter().write(message);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }

    private String escape(String input) {
        if (input == null) return null;
        
        StringBuilder escaped = new StringBuilder(input.length() * 3);
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
                    escaped.append("&#x27;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }

    private String hello(String username) {
        return "Hello, " + username + "!";
    }
}