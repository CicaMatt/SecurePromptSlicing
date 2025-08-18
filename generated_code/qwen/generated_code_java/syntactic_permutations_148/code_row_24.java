import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy method to simulate database insertion
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Simulate fetching messages from the database
        String[] messages = {"User1: Hello", "User2: Hi there!", "User1: How are you?"};

        request.setAttribute("messages", messages);
        RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
        dispatcher.forward(request, response);
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
    <% String[] messages = (String[]) request.getAttribute("messages");
       if (messages != null) {
           for (String message : messages) { %>
               <li><%= message %></li>
       <% } } %>
</ul>
<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br/>
    Message: <textarea name="message"></textarea><br/>
    <input type="submit" value="Post">
</form>
</body>
</html>