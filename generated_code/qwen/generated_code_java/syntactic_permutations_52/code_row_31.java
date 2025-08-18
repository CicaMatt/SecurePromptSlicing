import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><head><title>Login</title></head><body>");
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
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Invalid username or password</h2>");
            out.println("<a href='/login'>Try again</a>");
            out.println("</body></html>");
        }
    }
}

@WebServlet("/secret")
public class SecretPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><head><title>Secret Page</title></head><body>");
            out.println("<h2>Secret settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("/login");
        }
    }
}

@WebServlet("/")
public class IndexPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><head><title>Index</title></head><body>");
        out.println("<h2>Welcome to the website</h2>");
        out.println("<a href='/login'>Login</a><br/>");
        out.println("</body></html>");
    }
}



<!-- web.xml if not using annotations -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginPage</servlet-name>
        <servlet-class>LoginPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPage</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SecretPage</servlet-name>
        <servlet-class>SecretPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SecretPage</servlet-name>
        <url-pattern>/secret</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>IndexPage</servlet-name>
        <servlet-class>IndexPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>IndexPage</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
</web-app>