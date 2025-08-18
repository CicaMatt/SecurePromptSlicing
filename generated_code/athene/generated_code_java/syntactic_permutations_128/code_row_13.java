import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet {

    public void http_hello_page(HttpServletRequest request, HttpServletResponse response) {
        try {
            String username = request.getParameter("username");
            String greeting = "hello " + (username != null ? username : "world");
            response.setContentType("text/html;charset=UTF-8");
            response.getWriter().write(greeting);
        } catch (IOException e) {
            // Handle exception
        }
    }
}