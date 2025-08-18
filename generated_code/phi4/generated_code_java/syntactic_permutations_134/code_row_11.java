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
        
        if (pathInfo != null && pathInfo.startsWith("/")) {
            String username = pathInfo.substring(1);
            String escapedUsername = escape(username);
            
            response.setContentType("text/html");
            response.getWriter().write("<html><body>");
            response.getWriter().write(hello(escapedUsername));
            response.getWriter().write("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format.");
        }
    }

    private String hello(String username) {
        return "<h1>Hello, " + username + "</h1>";
    }

    private String escape(String input) {
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
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