import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect(request.getContextPath() + "/submit-message.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into database: User=" + username + ", Message=" + message);
    }
}

// submit-message.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Submit Message</title>
</head>
<body>
<h2>Submit a Message</h2>
<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br><br>
    Message: <textarea name="message" rows="4" cols="50"></textarea><br><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>