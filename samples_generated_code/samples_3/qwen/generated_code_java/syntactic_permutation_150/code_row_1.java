import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        
        response.sendRedirect("index.html");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Dummy implementation for database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Message Board</h1>
    <form action="MessageServlet" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/MessageServlet</url-pattern>
    </servlet-mapping>
</web-app>