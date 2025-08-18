import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to the main page
        } else {
            // Handle insertion failure, e.g., show an error message
            response.getWriter().write("Failed to submit your message.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Placeholder for database logic. In a real application, this would involve:
        // 1. Establishing a connection to the database.
        // 2. Preparing an SQL statement to insert the data.
        // 3. Executing the statement and returning whether it was successful.

        System.out.println("Inserting message for user: " + username);
        System.out.println("Message: " + message);

        // Simulate a successful database insertion
        return true;
    }
}

// mainPage.jsp (simplified example)
/*
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form action="submitMessage" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>
*/