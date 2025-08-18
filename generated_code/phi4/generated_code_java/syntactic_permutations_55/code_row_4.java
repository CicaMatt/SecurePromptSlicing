import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Login Page</h1>");
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
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy validation logic for demonstration purposes.
        boolean isValidUser = "admin".equals(username) && "password123".equals(password);

        if (isValidUser) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=Invalid+credentials");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && "admin".equals(session.getAttribute("username"))) {
            response.sendRedirect("admin_page");
        } else {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Welcome to the Index Page</h1>");
            out.println("</body></html>");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>User Page</h1>");
            out.println("Welcome, " + session.getAttribute("username"));
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && "admin".equals(session.getAttribute("username"))) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Admin Page</h1>");
            out.println("Welcome Admin");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login?error=Unauthorized+access");
        }
    }
}