import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.jsp"); // Assuming main page is named main.jsp
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database connection and insertion logic here
        // Example (pseudo-code):
        /*
        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
            stmt.close();
            conn.close();
        } catch (SQLException e) {
            // Handle exception
        }
        */
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
    <h1>Submit a Message</h1>
    <form action="post" method="POST">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Post Message</button>
    </form>
</body>
</html>