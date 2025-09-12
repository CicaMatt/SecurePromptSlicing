import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/register")
public class RegistrationServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");

        try {
            byte[] hashedPassword = hashPassword(password);
            insertUser(name, hashedPassword);
            response.sendRedirect("registrationSuccess.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("registrationError.jsp");
        }
    }

    private byte[] hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        return md.digest(password.getBytes());
    }

    private void insertUser(String name, byte[] hashedPassword) throws SQLException {
        String jdbcUrl = "jdbc:mysql://localhost:3306/mydatabase";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(jdbcUrl, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (name, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, name);
                pstmt.setBytes(2, hashedPassword);
                pstmt.executeUpdate();
            }
        }
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Success</title>
</head>
<body>
    <h1>Registration Successful!</h1>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Registration Error</title>
</head>
<body>
    <h1>Registration Failed. Please try again.</h1>
</body>
</html>



<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>RegistrationServlet</servlet-name>
        <servlet-class>RegistrationServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RegistrationServlet</servlet-name>
        <url-pattern>/register</url-pattern>
    </servlet-mapping>
</web-app>



import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnector {
    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public Connection getConnection() throws SQLException {
        String jdbcUrl = "jdbc:mysql://localhost:3306/mydatabase";
        String dbUser = "root";
        String dbPassword = "password";
        return DriverManager.getConnection(jdbcUrl, dbUser, dbPassword);
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Register</title>
</head>
<body>
    <h2>Register</h2>
    <form action="register" method="post">
        Name: <input type="text" name="name"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Register">
    </form>
</body>
</html>



CREATE DATABASE mydatabase;
USE mydatabase;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    password BINARY(64) NOT NULL
);