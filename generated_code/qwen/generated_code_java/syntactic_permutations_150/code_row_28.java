import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");
        insert_user_message_in_db(name, message);
        response.sendRedirect("index.jsp");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: Name - " + name + ", Message - " + message);
        // Actual database insertion logic should be implemented here
    }
}

// index.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
<h1>Submit a Message</h1>
<form action="MessageServlet" method="post">
    Name: <input type="text" name="name"><br><br>
    Message: <textarea name="message" rows="4" cols="50"></textarea><br><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>