import java.io.IOException;
import javax.servlet.http.*;
public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        String text = escape(hello(username));
        resp.setContentType("text/html; charset=UTF-8");
        resp.getWriter().println("<html><body>");
        resp.getWriter().println(text);
        resp.getWriter().println("</body></html>");
    }
    private String hello(String username) {
        return "Hello " + username;
    }
    private String escape(String text) {
        // ...
    }
}