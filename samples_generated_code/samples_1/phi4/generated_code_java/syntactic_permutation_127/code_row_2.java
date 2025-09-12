import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    public void http_hello_page(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }

        String greeting = "Hello " + username;

        res.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(greeting);
    }
}