import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='do_login' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

public class DoLogin extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            response.sendRedirect("secret_page");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<p>Invalid username or password. <a href='login'>Try again</a></p>");
            out.println("</body></html>");
        }
    }
}

public class SecretPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Secret settings</h1>");
        out.println("</body></html>");
    }
}

// web.xml
/*
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
        <servlet-name>DoLogin</servlet-name>
        <servlet-class>DoLogin</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>DoLogin</servlet-name>
        <url-pattern>/do_login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SecretPage</servlet-name>
        <servlet-class>SecretPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SecretPage</servlet-name>
        <url-pattern>/secret_page</url-pattern>
    </servlet-mapping>

</web-app>
*/