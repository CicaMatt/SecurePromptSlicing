import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/PostServlet")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to main page
        } else {
            response.getWriter().println("Failed to insert message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "root";  // Change this to your MySQL username
        String pass = "";      // Change this to your MySQL password

        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, user, pass);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        // For testing purposes only
        displayMessages();
    }

    private static void displayMessages() {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "root";  // Change this to your MySQL username
        String pass = "";      // Change this to your MySQL password

        String sql = "SELECT * FROM messages";

        try (Connection conn = DriverManager.getConnection(url, user, pass);
             java.sql.Statement stmt = conn.createStatement();
             java.sql.ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                System.out.println("Username: " + rs.getString("username") +
                        ", Message: " + rs.getString("message"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Ensure you have a table named `messages` with columns `username` and `message` in your database. Adjust the database URL, username, and password as necessary.