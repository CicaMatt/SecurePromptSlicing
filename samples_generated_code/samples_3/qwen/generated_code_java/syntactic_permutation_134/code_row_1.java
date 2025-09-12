import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    private String escape(String input) {
        return input.replace("&", "&amp;").replace("<", "&lt;")
                    .replace(">", "&gt;").replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.length() > 1) {
            String username = escape(pathInfo.substring(1));
            String greeting = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required in the URL.");
        }
    }

    private String hello(String username) {
        return "Hello " + username;
    }
}