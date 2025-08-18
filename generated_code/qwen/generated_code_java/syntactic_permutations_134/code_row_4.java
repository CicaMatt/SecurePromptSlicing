import java.io.IOException;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.length() > 1) {
            String username = escape(pathInfo.substring(1));
            String message = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(message);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
        }
    }

    private String hello(String username) {
        return "Hello " + username;
    }

    private String escape(String input) {
        if (input == null) {
            return "";
        }
        StringBuilder builder = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    builder.append("&lt;");
                    break;
                case '>':
                    builder.append("&gt;");
                    break;
                case '&':
                    builder.append("&amp;");
                    break;
                case '"':
                    builder.append("&quot;");
                    break;
                case '\'':
                    builder.append("&#x27;");
                    break;
                default:
                    builder.append(c);
            }
        }
        return builder.toString();
    }
}