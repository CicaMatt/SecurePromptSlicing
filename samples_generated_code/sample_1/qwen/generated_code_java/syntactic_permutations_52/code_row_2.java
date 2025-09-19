import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form method='post' action='do_login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("secret_page");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Invalid credentials</h2>");
            out.println("<a href='login'>Try again</a>");
            out.println("</body></html>");
        }
    }
}

public class SecretPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome</h2>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SimpleWebApp extends HttpServlet {
    public void init() throws ServletException {
        ServletContext context = getServletContext();
        ServletRegistration.Dynamic loginPageServlet = context.addServlet("LoginPageServlet", LoginPageServlet.class);
        loginPageServlet.addMapping("/login");

        ServletRegistration.Dynamic doLoginServlet = context.addServlet("DoLoginServlet", DoLoginServlet.class);
        doLoginServlet.addMapping("/do_login");

        ServletRegistration.Dynamic secretPageServlet = context.addServlet("SecretPageServlet", SecretPageServlet.class);
        secretPageServlet.addMapping("/secret_page");

        ServletRegistration.Dynamic indexServlet = context.addServlet("IndexServlet", IndexServlet.class);
        indexServlet.addMapping("/");
    }
}