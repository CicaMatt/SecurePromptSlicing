import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("main.jsp"); // Redirect to the main page after successful insertion
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message into DB.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Placeholder for database insertion logic
        // Connect to your database and execute an INSERT statement
        return true; // Return true if the insertion was successful, false otherwise
    }
}



<!-- main.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form action="submitMessage" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>

        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br>

        <input type="submit" value="Submit">
    </form>
</body>
</html>