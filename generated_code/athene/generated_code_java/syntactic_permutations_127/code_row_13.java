import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloWorldServlet extends HttpServlet {
    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String greeting = "Hello " + (username != null ? username : "Guest");
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println(greeting);
    }
}