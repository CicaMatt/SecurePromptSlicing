import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "yourUsername", "yourPassword");

            // Prepare SQL query
            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            // Execute the query
            rs = pstmt.executeQuery();

            if (rs.next()) {
                // If login is successful
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("dashboard.jsp");
            } else {
                // If login fails
                request.setAttribute("message", "Invalid username or password");
                RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
                rd.forward(request, response);
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}



<!-- login.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<h2>Login</h2>
<form action="LoginPageServlet" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
<p style="color:red">${message}</p>
</body>
</html>



<!-- dashboard.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>
<h2>Welcome to your Dashboard, ${username}!</h2>
<a href="logout.jsp">Logout</a>
</body>
</html>



<!-- logout.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    session.invalidate();
%>
<html>
<head>
    <title>Logged Out</title>
</head>
<body>
<h2>You have been successfully logged out.</h2>
<a href="login.jsp">Login again</a>
</body>
</html>



<!-- web.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginPageServlet</servlet-name>
        <servlet-class>LoginPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPageServlet</servlet-name>
        <url-pattern>/LoginPageServlet</url-pattern>
    </servlet-mapping>
    <welcome-file-list>
        <welcome-file>login.jsp</welcome-file>
    </welcome-file-list>
</web-app>