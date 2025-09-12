import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy authentication logic
        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        PrintWriter out = response.getWriter();
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.sendRedirect("admin_page");
        } else if (session != null) {
            response.sendRedirect("user_page");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.sendRedirect("admin_page");
        } else if (session != null) {
            out.println("<html><body>");
            out.println("<h1>Welcome, User!</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        PrintWriter out = response.getWriter();
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.setContentType("text/html");
            out.println("<html><body>");
            out.println("<h1>Welcome, Admin!</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}