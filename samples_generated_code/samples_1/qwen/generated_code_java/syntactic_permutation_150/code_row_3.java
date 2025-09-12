import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("index.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }
}

<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <form action="MessageServlet" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>