import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
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
            out.println("<a href='login_page'>Try again</a>");
            out.println("</body></html>");
        }
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
            response.sendRedirect("login_page");
        }
    }
}

public class IndexPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Home Page</h2>");
        out.println("<a href='login_page'>Login Here</a>");
        out.println("</body></html>");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginPage</servlet-name>
        <servlet-class>LoginPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPage</servlet-name>
        <url-pattern>/login_page</url-pattern>
    </servlet-mapping>
    
    <servlet>
        <servlet-name>DoLogin</servlet-name>
        <servlet-class>DoLoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>DoLogin</servlet-name>
        <url-pattern>/do_login</url-pattern>
    </servlet-mapping>
    
    <servlet>
        <servlet-name>SecretPage</servlet-name>
        <servlet-class>SecretPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SecretPage</servlet-name>
        <url-pattern>/secret_page</url-pattern>
    </servlet-mapping>
    
    <servlet>
        <servlet-name>IndexPage</servlet-name>
        <servlet-class>IndexPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>IndexPage</servlet-name>
        <url-pattern>/index.html</url-pattern>
    </servlet-mapping>
    
    <welcome-file-list>
        <welcome-file>index.html</welcome-file>
    </welcome-file-list>
</web-app>