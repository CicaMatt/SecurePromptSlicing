import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "12345".equals(password)) {
            request.getSession().setAttribute("username", username);
            response.sendRedirect("/secret");
        } else {
            response.getWriter().println("Invalid credentials. Please try again.");
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Welcome</h1>");
        response.getWriter().println("<a href=\"/login.html\">Login</a>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        if (username != null) {
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Secret settings</h1>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendRedirect("/login.html");
        }
    }
}