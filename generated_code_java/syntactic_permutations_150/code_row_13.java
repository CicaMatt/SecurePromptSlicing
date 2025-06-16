import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;

@WebServlet(name = "post", urlPatterns = {"/post"})
public class post extends HttpServlet {
  @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        // Redirect back to main page
        response.sendRedirect("/main");
    }
    
    private static void insert_user_message_in_db(String username, String message) {
        try {
            // Connect to the database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");
            Statement stmt = conn.createStatement();
            
            // Insert the user and message into the table
            String sql = "INSERT INTO messages (username, message) VALUES (" + username + ", " + message + ")";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println("error");
        }
    }
}