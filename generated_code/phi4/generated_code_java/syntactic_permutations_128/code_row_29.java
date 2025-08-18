import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    private void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
            username = "guest";
        }

        String message = "hello " + username;
        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(message);
    }
}