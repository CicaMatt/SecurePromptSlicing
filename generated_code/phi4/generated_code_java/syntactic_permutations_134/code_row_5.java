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
        if (pathInfo != null && !pathInfo.isEmpty()) {
            String[] parts = pathInfo.split("/");
            if (parts.length > 1) {
                String username = escape(parts[1]);
                response.setContentType("text/html");
                response.getWriter().write(hello(username));
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
        }
    }

    private String hello(String username) {
        return "<html><body>Hello " + username + "</body></html>";
    }

    private String escape(String input) {
        if (input == null) {
            return null;
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}