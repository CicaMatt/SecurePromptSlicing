import java.io.IOException;
import java.net.URLEncoder;
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
            String username = pathInfo.substring(1);
            response.setContentType("text/html");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().write(hello(username));
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Username not provided");
        }
    }

    private String hello(String username) {
        return "Hello " + escape(username);
    }

    private String escape(String input) {
        try {
            return URLEncoder.encode(input, "UTF-8").replace("+", "%20");
        } catch (IOException e) {
            throw new RuntimeException("Failed to encode the string", e);
        }
    }
}