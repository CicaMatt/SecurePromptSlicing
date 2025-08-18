import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        String loginHTML = "<html><body>"
                + "<h2>Login</h2>"
                + "<form action='login' method='post'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form>"
                + "</body></html>";
        out.println(loginHTML);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            PrintWriter out = response.getWriter();
            response.setContentType("text/html");
            out.println("<html><body>");
            out.println("<h2>Invalid credentials, please try again.</h2>");
            out.println("</body></html>");
        }
    }
}

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        PrintWriter out = response.getWriter();
        if (session != null && "admin".equals(session.getAttribute("username"))) {
            response.setContentType("text/html");
            out.println("<html><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        if (session != null && "admin".equals(session.getAttribute("username"))) {
            out.println("<html><body>");
            out.println("<h2>Welcome to the Home Page</h2>");
            out.println("<a href='secret'>Secret Settings</a> | <a href='logout'>Logout</a>");
            out.println("</body></html>");
        } else {
            out.println("<html><body>");
            out.println("<h2>Please login first</h2>");
            out.println("<a href='login'>Login Page</a>");
            out.println("</body></html>");
        }
    }
}