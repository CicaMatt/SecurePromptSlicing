import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming the main page is named mainPage.jsp
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database connection and insertion logic goes here.
        // This is a placeholder for actual database interaction code.
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        // Example: JDBC code to connect to the database and insert data
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
    <h1>Submit a Message</h1>
    <form action="post" method="POST">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>

        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br><br>

        <button type="submit">Submit</button>
    </form>
</body>
</html>


Note: The `insertUserMessageInDb` function is a placeholder and should be implemented with actual database interaction logic, typically using JDBC or another Java database connectivity framework. Ensure that the necessary database driver JAR files are included in your project's classpath.