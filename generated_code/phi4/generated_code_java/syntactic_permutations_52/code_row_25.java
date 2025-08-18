import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "12345".equals(password)) { // Replace with actual authentication
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("home");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>");
        response.getWriter().write("<form action='login' method='POST'>");
        response.getWriter().write("Username: <input type='text' name='username'><br>");
        response.getWriter().write("Password: <input type='password' name='password'><br>");
        response.getWriter().write("<input type='submit' value='Login'>");

        if (request.getParameter("error") != null) {
            response.getWriter().write("<p>Invalid username or password!</p>");
        }
        response.getWriter().write("</form>");
        response.getWriter().write("</body></html>");
    }
}

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>");
            response.getWriter().write("Welcome! <a href='secret'>Secret Settings</a> | ");
            response.getWriter().write("<a href='logout'>Logout</a>");
            response.getWriter().write("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && "admin".equals(session.getAttribute("username"))) {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>");
            response.getWriter().write("<h1>Secret settings</h1>");
            response.getWriter().write("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login");
    }
}