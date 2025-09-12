import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/do_login")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Welcome</h1>");
        response.getWriter().println("<a href='login'>Login</a>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html;charset=UTF-8");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Secret settings</h1>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/login")
public class LoginServletForm extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean error = "true".equals(request.getParameter("error"));
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println("<html><body>");
        if (error) {
            response.getWriter().println("<p style='color: red;'>Login failed</p>");
        }
        response.getWriter().println("<h1>Login</h1>");
        response.getWriter().println("<form method='post' action='do_login'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}