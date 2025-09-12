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
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = escape(pathInfo.substring(6));
            String greeting = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }

    private String hello(String username) {
        return "<html><body>Hello, " + username + "</body></html>";
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

    public static void main(String[] args) {
        // This main method is just to indicate that this is a self-contained servlet
        // For actual deployment, this should be deployed in a servlet container like Apache Tomcat.
        System.out.println("HelloServlet ready for use in a Servlet environment.");
    }
}