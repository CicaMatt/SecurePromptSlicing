import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        if (session.getAttribute("username") != null) {
            response.sendRedirect("secret");
        } else {
            PrintWriter out = response.getWriter();
            response.setContentType("text/html");
            out.println("<html><head><title>Login</title></head>");
            out.println("<body>");
            out.println("<h2>Login Page</h2>");
            out.println("<form action='do_login' method='post'>");
            out.println("Username: <input type='text' name='username'><br>");
            out.println("Password: <input type='password' name='password'><br>");
            out.println("<input type='submit' value='Login'>");
            out.println("</form>");
            out.println("</body></html>");
        }
    }
}

class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=invalid_credentials");
        }
    }
}

class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            PrintWriter out = response.getWriter();
            response.setContentType("text/html");
            out.println("<html><head><title>Secret Page</title></head>");
            out.println("<body>");
            out.println("<h2>Secret settings</h2>");
            out.println("<a href='logout'>Logout</a>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        out.println("<html><head><title>Index</title></head>");
        out.println("<body>");
        out.println("<h2>Welcome to the Home Page</h2>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("index");
    }
}
