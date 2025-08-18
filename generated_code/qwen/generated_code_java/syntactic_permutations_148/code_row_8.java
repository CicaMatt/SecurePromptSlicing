import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.List;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Implement database insertion logic here
        System.out.println("Inserting into DB: " + username + ", " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDB();

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
        dispatcher.forward(request, response);
    }

    private List<String> getMessagesFromDB() {
        // Implement database retrieval logic here
        return List.of("Message 1 from User 1", "Message 2 from User 2");
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
    <% for (String message : (List<String>) request.getAttribute("messages")) { %>
        <li><%= message %></li>
    <% } %>
</ul>
<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>