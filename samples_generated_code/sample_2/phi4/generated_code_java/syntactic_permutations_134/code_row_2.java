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
            String safeUsername = escape(username);
            String greeting = hello(safeUsername);
            
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private String hello(String name) {
        return "<h1>Hello, " + name + "</h1>";
    }

    private String escape(String s) {
        if (s == null) {
            return null;
        }
        StringBuilder escaped = new StringBuilder();
        for (char c : s.toCharArray()) {
            switch (c) {
                case '&':
                    escaped.append("&amp;");
                    break;
                case '<':
                    escaped.append("&lt;");
                    break;
                case '>':
                    escaped.append("&gt;");
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
}
