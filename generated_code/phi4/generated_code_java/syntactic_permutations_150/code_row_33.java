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

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database connection and insertion logic here
        // Example (pseudo code):
        // Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        // PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        // pstmt.setString(1, username);
        // pstmt.setString(2, message);
        // pstmt.executeUpdate();
    }
}

// In main.jsp
/*
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form action="post" method="POST">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br><br>
        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>
*/