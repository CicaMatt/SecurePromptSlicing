import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import org.mindrot.jbcrypt.BCrypt;

public class RegisterServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        Connection conn = null;
        PreparedStatement ps = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "user", "password");

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            ps = conn.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, hashedPassword);

            int rowsAffected = ps.executeUpdate();
            if (rowsAffected > 0) {
                response.sendRedirect("registrationSuccess.jsp");
            } else {
                response.sendRedirect("registrationError.jsp");
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        } finally {
            try {
                if (ps != null) ps.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RegistrationSuccessServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Registration Successful!</h2>");
        out.println("</body></html>");
    }
}



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RegistrationErrorServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Registration Failed!</h2>");
        out.println("</body></html>");
    }
}



<!-- registration.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Register</title>
</head>
<body>
<h1>Register</h1>
<form action="register" method="post">
    Username: <input type="text" name="username"><br/>
    Password: <input type="password" name="password"><br/>
    <input type="submit" value="Register">
</form>
</body>
</html>



<!-- registrationSuccess.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Success</title>
</head>
<body>
<h2>Registration Successful!</h2>
<a href="registration.jsp">Register another user</a>
</body>
</html>



<!-- registrationError.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Error</title>
</head>
<body>
<h2>Registration Failed!</h2>
<a href="registration.jsp">Try again</a>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>RegisterServlet</servlet-name>
        <servlet-class>RegisterServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegisterServlet</servlet-name>
        <url-pattern>/register</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>RegistrationSuccessServlet</servlet-name>
        <servlet-class>RegistrationSuccessServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegistrationSuccessServlet</servlet-name>
        <url-pattern>/registrationSuccess.jsp</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>RegistrationErrorServlet</servlet-name>
        <servlet-class>RegistrationErrorServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegistrationErrorServlet</servlet-name>
        <url-pattern>/registrationError.jsp</url-pattern>
    </servlet-mapping>

    <welcome-file-list>
        <welcome-file>registration.jsp</welcome-file>
    </welcome-file-list>
</web-app>



-- SQL to create the users table
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);