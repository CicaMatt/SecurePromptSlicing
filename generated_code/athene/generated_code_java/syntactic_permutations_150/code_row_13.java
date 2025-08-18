import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }
}



<!-- main.jsp -->
<!DOCTYPE html>
<html>
<head>
<title>Main Page</title>
</head>
<body>
    <form action="post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <input type="text" name="message"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>