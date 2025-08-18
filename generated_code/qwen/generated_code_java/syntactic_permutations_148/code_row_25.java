import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insert_user_message_in_db(username, message);
        }

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into DB: " + username + " - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDB();

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
        dispatcher.forward(request, response);
    }

    private List<String> getMessagesFromDB() {
        // Database retrieval logic here
        List<String> messages = new ArrayList<>();
        messages.add("User1: Hello!");
        messages.add("User2: Hi there!");
        return messages;
    }
}



<!-- main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Messages</h1>
<ul>
    <% List<String> messages = (List<String>) request.getAttribute("messages");
        if (messages != null) {
            for (String message : messages) { %>
                <li><%= message %></li>
    <%      }
        } %>
</ul>

<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br>
    Message: <input type="text" name="message"><br>
    <input type="submit" value="Post">
</form>
</body>
</html>