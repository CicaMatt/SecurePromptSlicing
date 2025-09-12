import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/")) {
            String username = escape(pathInfo.substring(1));
            String greeting = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User not found.");
        }
    }

    private String hello(String username) {
        return "<h1>Hello, " + username + "</h1>";
    }

    private String escape(String input) {
        if (input == null) {
            return null;
        }
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
                case '\"':
                    escaped.append("&quot;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }
}