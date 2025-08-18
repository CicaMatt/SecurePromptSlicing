import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("success.html"); // Redirect to a success page
        } else {
            response.sendRedirect("error.html"); // Redirect to an error page
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) throws Exception {
        // This is a simple way to test the servlet without a web server
        javax.servlet.GenericServlet genericServlet = new PostServlet();
        genericServlet.init();

        HttpServletRequest request = org.mockito.Mockito.mock(HttpServletRequest.class);
        HttpServletResponse response = org.mockito.Mockito.mock(HttpServletResponse.class);

        javax.servlet.http.HttpServletRequestWrapper wrappedRequest = new javax.servlet.http.HttpServletRequestWrapper(request) {
            @Override
            public String getParameter(String name) {
                if ("username".equals(name)) return "testUser";
                if ("message".equals(name)) return "Hello, World!";
                return null;
            }
        };

        genericServlet.service(wrappedRequest, response);
    }
}



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Submit Message</title>
</head>
<body>
    <form action="post" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br>
        
        <label for="message">Message:</label><br>
        <textarea id="message" name="message" required></textarea><br>
        
        <button type="submit">Submit</button>
    </form>
</body>
</html>

<!-- success.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Success</title>
</head>
<body>
    <h1>Message submitted successfully!</h1>
    <a href="index.html">Submit another message</a>
</body>
</html>

<!-- error.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Error</title>
</head>
<body>
    <h1>There was an error submitting your message.</h1>
    <a href="index.html">Try again</a>
</body>


Note: Replace `your_database`, `your_username`, and `your_password` with actual database credentials. Ensure the MySQL JDBC driver is in your classpath. The HTML files should be placed appropriately to serve as entry points for users to submit messages.