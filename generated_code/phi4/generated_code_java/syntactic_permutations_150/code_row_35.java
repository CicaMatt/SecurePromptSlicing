import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect(request.getContextPath() + "/main.jsp");
        } else {
            throw new ServletException("Failed to insert the user message into the database.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting message from " + username + ": " + message);
        return true; // Assume insertion is successful for this example
    }
}



<!-- main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form action="post" method="POST">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>


This code includes a servlet `PostServlet` that handles the form submission and redirects to `main.jsp`. The JSP file contains a simple form for submitting messages. Note that the database logic in `insert_user_message_in_db()` is simulated with a print statement and should be replaced with actual database interaction code.