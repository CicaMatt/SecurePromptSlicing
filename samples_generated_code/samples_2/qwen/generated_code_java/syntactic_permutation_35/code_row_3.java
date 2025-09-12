import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "user".equals(username) && "pass".equals(password);
    }
}

import java.io.*;

public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Home Page</h1>");
        out.println("</body></html>");
    }
}

import java.io.*;

public class LoginHTMLServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form method='post' action='login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

import javax.servlet.*;
import javax.servlet.http.*;

public class WebAppInitializer implements ServletContainerInitializer {
    @Override
    public void onStartup(Set<Class<?>> c, ServletContext ctx) throws ServletException {
        ServletRegistration.Dynamic loginServlet = ctx.addServlet("LoginServlet", LoginServlet.class);
        loginServlet.addMapping("/login");

        ServletRegistration.Dynamic homeServlet = ctx.addServlet("HomeServlet", HomeServlet.class);
        homeServlet.addMapping("/home.html");

        ServletRegistration.Dynamic loginHTMLServlet = ctx.addServlet("LoginHTMLServlet", LoginHTMLServlet.class);
        loginHTMLServlet.addMapping("/login.html");
    }
}