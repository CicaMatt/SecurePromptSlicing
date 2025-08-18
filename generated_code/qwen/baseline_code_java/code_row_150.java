import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Actual database insertion logic should be implemented here
    }
}

// index.html
/*
<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form action="post" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
*/



import java.io.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Actual database insertion logic should be implemented here
    }
}