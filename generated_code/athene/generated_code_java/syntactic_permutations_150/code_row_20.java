import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insert_user_message_in_db(message);
        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String message) {
        // Database insertion logic here
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <form action="post" method="post">
        <label for="message">Message:</label><br>
        <input type="text" id="message" name="message"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>