import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.sendRedirect("secret");
        } else {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Login</h2>");
            out.println("<form method='post' action='login'>");
            out.println("Username: <input type='text' name='username'><br>");
            out.println("Password: <input type='password' name='password'><br>");
            out.println("<input type='submit' value='Login'>");
            out.println("</form></body></html>");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            doGet(request, response);
        }
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("<a href='logout'>Logout</a>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome</h2>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WebApp extends HttpServlet {
    public void init() throws ServletException {
        getServletContext().getServletRegistration("index").addMapping("/");
        getServletContext().getServletRegistration("login").addMapping("/login");
        getServletContext().getServletRegistration("secret").addMapping("/secret");
        getServletContext().getServletRegistration("logout").addMapping("/logout");
    }
}

import javax.servlet.*;
import javax.servlet.http.*;

public class WebAppInitializer extends HttpServlet {
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        ServletContext context = getServletContext();

        Servlet indexServlet = new IndexServlet();
        Servlet loginServlet = new LoginServlet();
        Servlet secretServlet = new SecretServlet();
        Servlet logoutServlet = new LogoutServlet();

        context.addServlet("index", indexServlet).addMapping("/");
        context.addServlet("login", loginServlet).addMapping("/login");
        context.addServlet("secret", secretServlet).addMapping("/secret");
        context.addServlet("logout", logoutServlet).addMapping("/logout");
    }
}