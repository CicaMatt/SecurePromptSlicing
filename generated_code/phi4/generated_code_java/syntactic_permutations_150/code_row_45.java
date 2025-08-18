import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("mainPage.jsp");
    }

    private void insert_user_message_in_db(String name, String message) {
        // Database insertion logic here
        System.out.println("Inserting into database: " + name + ", " + message);
        // Implement actual database connection and insertion code.
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
        Name: <input type="text" name="name" required><br>
        Message: <textarea name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>