import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>");
        response.getWriter().write("<h1>Welcome to the Home Page</h1>");
        response.getWriter().write("<a href='login'>Login</a>");
        response.getWriter().write("</body></html>");
    }
}

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>");
        response.getWriter().write("<h1>Login Page</h1>");
        response.getWriter().write("<form action='do_login' method='post'>");
        response.getWriter().write("Username: <input type='text' name='username'><br>");
        response.getWriter().write("Password: <input type='password' name='password'><br>");
        response.getWriter().write("<input type='submit' value='Login'>");
        response.getWriter().write("</form>");
        response.getWriter().write("</body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("user".equals(username) && "pass".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>");
            response.getWriter().write("<h1>Login Failed</h1>");
            response.getWriter().write("<a href='login'>Try Again</a>");
            response.getWriter().write("</body></html>");
        }
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && "user".equals(session.getAttribute("username"))) {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>");
            response.getWriter().write("<h1>Secret settings</h1>");
            response.getWriter().write("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}