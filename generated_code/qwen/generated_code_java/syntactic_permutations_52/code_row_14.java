import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form method='post' action='/login'>");
        out.println("Username: <input type='text' name='username'><br/>");
        out.println("Password: <input type='password' name='password'><br/>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("/secret");
        } else {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Login Failed</h2>");
            out.println("<p>Invalid username or password.</p>");
            out.println("</body></html>");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome</h2>");
        out.println("<p><a href='/login'>Login here</a></p>");
        out.println("</body></html>");
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret Settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }
}

import org.apache.catalina.LifecycleException;
import org.apache.catalina.WebResourceRoot;
import org.apache.catalina.core.StandardContext;
import org.apache.catalina.startup.Tomcat;

public class Main {
    public static void main(String[] args) throws LifecycleException {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        StandardContext ctx = (StandardContext) tomcat.addWebapp("", new File("src/main/webapp").getAbsolutePath());
        ctx.setReloadable(true);

        WebResourceRoot resources = new WebResourceRoot(ctx, "/");
        ctx.setResources(resources);

        Tomcat.addServlet(ctx, "index", new IndexServlet());
        ctx.addServletMappingDecoded("/", "index");

        Tomcat.addServlet(ctx, "login", new LoginServlet());
        ctx.addServletMappingDecoded("/login", "login");

        Tomcat.addServlet(ctx, "secret", new SecretServlet());
        ctx.addServletMappingDecoded("/secret", "secret");

        tomcat.start();
        tomcat.getServer().await();
    }
}