import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("displayMessages.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy method to simulate database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Actual database insertion logic should go here
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Display Messages</title>
</head>
<body>
<h1>Messages:</h1>
<ul>
    <!-- Dummy list item to simulate message display -->
    <li>User: John, Message: Hello World!</li>
    <!-- Actual logic to fetch and display messages from the database should go here -->
</ul>
<a href="postMessage.jsp">Add New Message</a>
</body>
</html>