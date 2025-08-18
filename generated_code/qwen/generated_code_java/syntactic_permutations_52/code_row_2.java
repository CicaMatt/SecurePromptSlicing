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
            response.sendRedirect("login.jsp?error=1");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Home Page</h2>");
        out.println("<a href='login.jsp'>Login</a>");
        out.println("</body></html>");
    }
}

// login.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<h2>Login</h2>
<form action="do_login" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
<%
    if ("1".equals(request.getParameter("error"))) {
        out.println("<p style='color:red;'>Invalid username or password.</p>");
    }
%>
</body>
</html>

// secret.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Secret Page</title>
</head>
<body>
<h2>Secret settings</h2>
<a href='index.jsp'>Back to Home</a>
</body>
</html>

// web.xml
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>IndexServlet</servlet-name>
        <servlet-class>IndexServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>IndexServlet</servlet-name>
        <url-pattern>/index.jsp</url-pattern>
    </servlet-mapping>
    <servlet>
        <servlet-name>LoginServlet</servlet-name>
        <servlet-class>LoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginServlet</servlet-name>
        <url-pattern>/do_login</url-pattern>
    </servlet-mapping>
</web-app>