import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/SubmitMessage")
public class SubmitMessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming the main page is 'mainPage.jsp'
    }

    private void insert_user_message_in_db(String username, String message) {
        // Code to insert user and message into database
        // This can be implemented using JDBC or any ORM framework like Hibernate
        System.out.println("Inserting into DB: Username = " + username + ", Message = " + message);
        // Example placeholder for actual implementation
    }
}



<!-- mainPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form action="SubmitMessage" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br><br>

        <label for="message">Message:</label><br>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>

        <button type="submit">Submit</button>
    </form>
</body>
</html>