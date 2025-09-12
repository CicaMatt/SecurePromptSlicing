import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        
        response.sendRedirect("main.jsp");
    }
    
    private void insert_user_message_in_db(String username, String message) {
        // Dummy method to simulate database insertion
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
    }
}



<!-- main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form action="MessageServlet" method="post">
        Username: <input type="text" name="username"><br><br>
        Message: <textarea name="message"></textarea><br><br>
        <input type="submit" value="Submit Message">
    </form>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/MessageServlet</url-pattern>
    </servlet-mapping>
    <welcome-file-list>
        <welcome-file>main.jsp</welcome-file>
    </welcome-file-list>
</web-app>