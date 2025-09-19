import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("success.jsp"); // Redirect to a success page or back to the form
        } else {
            response.sendRedirect("error.jsp"); // Redirect to an error page if insertion fails
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting message from " + username + ": " + message);
        return true; // Return true if insertion is successful, false otherwise
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Submit Message</title>
</head>
<body>
    <form action="post" method="POST">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br><br>

        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br><br>

        <button type="submit">Submit</button>
    </form>
</body>
</html>



// Assuming a simple JSP file for success.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Success</title>
</head>
<body>
    <h1>Your message has been submitted successfully!</h1>
    <a href="index.html">Go back to the form</a>
</body>
</html>



// Assuming a simple JSP file for error.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Error</title>
</head>
<body>
    <h1>There was an error submitting your message. Please try again.</h1>
    <a href="index.html">Go back to the form</a>
</body>
</html>