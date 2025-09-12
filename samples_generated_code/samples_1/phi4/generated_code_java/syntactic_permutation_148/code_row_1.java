import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(name, message)) {
            response.sendRedirect("main.jsp");
        } else {
            response.getWriter().append("Error inserting message.");
        }
    }

    private boolean insertUserMessageInDB(String name, String message) {
        String sql = "INSERT INTO messages (name, message) VALUES (?, ?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, name);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}



import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/main")
public class MainServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("SELECT name, message FROM messages")) {

            ResultSet rs = pstmt.executeQuery();

            StringBuilder sb = new StringBuilder("<html><body>");
            while (rs.next()) {
                String name = rs.getString("name");
                String message = rs.getString("message");

                sb.append("<p>").append(name).append(": ").append(message).append("</p>");
            }
            sb.append("</body></html>");

            response.getWriter().write(sb.toString());
        } catch (SQLException e) {
            e.printStackTrace();
            response.getWriter().append("Error fetching messages.");
        }
    }
}



import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/form")
public class FormServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().append("<html><body>");
        response.getWriter().append("<form action='post' method='POST'>");
        response.getWriter().append("Name: <input type='text' name='name'><br>");
        response.getWriter().append("Message: <textarea name='message'></textarea><br>");
        response.getWriter().append("<button type='submit'>Submit</button>");
        response.getWriter().append("</form>");
        response.getWriter().append("</body></html>");
    }
}



import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/main.jsp")
public class MainJspServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.sendRedirect("main");
    }
}


**Database Configuration:**

Make sure you have a MySQL database named `yourdatabase` with a table `messages` having columns `name` and `message`.


CREATE DATABASE yourdatabase;

USE yourdatabase;

CREATE TABLE messages (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    message TEXT NOT NULL
);


**Deployment Descriptor (web.xml):**


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>postServlet</servlet-name>
        <servlet-class>PostServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>postServlet</servlet-name>
        <url-pattern>/post</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>MainServlet</servlet-name>
        <servlet-class>MainServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/main</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>FormServlet</servlet-name>
        <servlet-class>FormServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>FormServlet</servlet-name>
        <url-pattern>/form</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>MainJspServlet</servlet-name>
        <servlet-class>MainJspServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>MainJspServlet</servlet-name>
        <url-pattern>/main.jsp</url-pattern>
    </servlet-mapping>
</web-app>