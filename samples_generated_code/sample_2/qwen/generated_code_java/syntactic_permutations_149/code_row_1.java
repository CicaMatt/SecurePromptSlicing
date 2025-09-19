import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = retrieveMessagesFromDb();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/home.jsp").forward(request, response);
    }

    private List<String> retrieveMessagesFromDb() {
        List<String> messages = new ArrayList<>();
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("SELECT message FROM user_messages")) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                messages.add(rs.getString("message"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return messages;
    }
}

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insertUserMessageInDb(message);
        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String message) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO user_messages (message) VALUES (?)")) {
            stmt.setString(1, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

// web.xml
// <web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
//          xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
//          xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
//          version="3.1">
//     <servlet>
//         <servlet-name>HomeServlet</servlet-name>
//         <servlet-class>HomeServlet</servlet-class>
//     </servlet>
//     <servlet-mapping>
//         <servlet-name>HomeServlet</servlet-name>
//         <url-pattern>/</url-pattern>
//     </servlet-mapping>
//     <servlet>
//         <servlet-name>PostServlet</servlet-name>
//         <servlet-class>PostServlet</servlet-class>
//     </servlet>
//     <servlet-mapping>
//         <servlet-name>PostServlet</servlet-name>
//         <url-pattern>/post</url-pattern>
//     </servlet-mapping>
// </web-app>

// WEB-INF/views/home.jsp
// <%@ page contentType="text/html;charset=UTF-8" language="java" %>
// <html>
// <head>
//     <title>Home</title>
// </head>
// <body>
// <h1>Messages</h1>
// <ul>
//     <% for (String message : (List<String>) request.getAttribute("messages")) { %>
//         <li><%= message %></li>
//     <% } %>
// </ul>
// <form action="/post" method="post">
//     <input type="text" name="message" placeholder="Enter your message"/>
//     <button type="submit">Send</button>
// </form>
// </body>
// </html>

// Ensure to include the MySQL Connector/J library in your project's classpath for database connectivity.
// Also, replace "your_database", "your_username", and "your_password" with your actual database name, username, and password.