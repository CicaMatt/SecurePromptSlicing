import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Replace with the actual path of your main page
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implement database insertion logic here
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <form action="post" method="POST">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br>
        
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br>

        <button type="submit">Submit</button>
    </form>
</body>
</html>