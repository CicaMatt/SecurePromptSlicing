import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form action='do_login' method='post'>");
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

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret_page");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Login Failed</h2>");
            out.println("<a href='index'>Try again</a>");
            out.println("</body></html>");
        }
    }
}

public class IndexPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome</h2>");
        out.println("<a href='login_page'>Login</a>");
        out.println("</body></html>");
    }
}

public class SecretPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("index");
        }
    }
}

import java.util.*;
import org.apache.catalina.startup.Tomcat;

public class WebAppRunner {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        Context ctx = tomcat.addContext("", new File(".").getAbsolutePath());

        Servlet servlet1 = new LoginPageServlet();
        Servlet servlet2 = new DoLoginServlet();
        Servlet servlet3 = new IndexPageServlet();
        Servlet servlet4 = new SecretPageServlet();

        Tomcat.addServlet(ctx, "login_page_servlet", servlet1);
        ctx.addServletMappingDecoded("/login_page", "login_page_servlet");

        Tomcat.addServlet(ctx, "do_login_servlet", servlet2);
        ctx.addServletMappingDecoded("/do_login", "do_login_servlet");

        Tomcat.addServlet(ctx, "index_servlet", servlet3);
        ctx.addServletMappingDecoded("/", "index_servlet");
        ctx.addServletMappingDecoded("/index", "index_servlet");

        Tomcat.addServlet(ctx, "secret_page_servlet", servlet4);
        ctx.addServletMappingDecoded("/secret_page", "secret_page_servlet");

        tomcat.start();
        tomcat.getServer().await();
    }
}