import java.io.*;
import java.util.*;
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
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = get_messages_from_db();

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
        dispatcher.forward(request, response);
    }

    private List<String> get_messages_from_db() {
        // Dummy implementation for demonstration purposes
        return Arrays.asList(
            "User1: Hello!",
            "User2: Hi there!",
            "User3: Good day!"
        );
    }
}

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        <% List<String> messages = (List<String>) request.getAttribute("messages");
           for (String message : messages) { %>
            <li><%= message %></li>
        <% } %>
    </ul>
    <form action="postMessage" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>

<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>MainServlet</servlet-name>
        <servlet-class>MainServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/main</url-pattern>
    </servlet-mapping>
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/postMessage</url-pattern>
    </servlet-mapping>
</web-app>