import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("login.html?error=1");
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("Welcome to the secret page!");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login.html");
        }
    }
}

import java.io.*;

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<a href='login.html'>Login</a>");
        out.println("</body></html>");
    }
}

<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <h2>Login</h2>
    <form method="post" action="login">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    <% if ("1".equals(request.getParameter("error"))) { %>
        <p style="color:red;">Invalid username or password.</p>
    <% } %>
</body>
</html>

<!DOCTYPE html>
<html>
<head>
    <title>Secret Page</title>
</head>
<body>
    Welcome to the secret page!
</body>
</html>


**web.xml**

<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginServlet</servlet-name>
        <servlet-class>LoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginServlet</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SecretServlet</servlet-name>
        <servlet-class>SecretServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SecretServlet</servlet-name>
        <url-pattern>/secret.jsp</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>IndexServlet</servlet-name>
        <servlet-class>IndexServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>IndexServlet</servlet-name>
        <url-pattern>/index.jsp</url-pattern>
    </servlet-mapping>
</web-app>