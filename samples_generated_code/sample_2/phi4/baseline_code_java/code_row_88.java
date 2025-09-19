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
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("main.jsp"); // Redirect to the main page
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to save message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // This method should contain logic to insert the message into the database.
        // For demonstration purposes, we'll just return true as if it was successful.

        // Example:
        // Connection conn = null;
        // PreparedStatement pstmt = null;

        // try {
        //     conn = DriverManager.getConnection(DB_URL, USER, PASS);
        //     String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        //     pstmt = conn.prepareStatement(sql);
        //     pstmt.setString(1, username);
        //     pstmt.setString(2, message);

        //     int affectedRows = pstmt.executeUpdate();
        //     return affectedRows > 0;
        // } catch (SQLException e) {
        //     e.printStackTrace();
        // } finally {
        //     if (pstmt != null) try { pstmt.close(); } catch (SQLException ignore) {}
        //     if (conn != null) try { conn.close(); } catch (SQLException ignore) {}
        // }

        return true;
    }
}



<!-- main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Welcome to the Message Board</h1>

<form action="post" method="POST">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <button type="submit">Submit</button>
</form>
</body>
</html>