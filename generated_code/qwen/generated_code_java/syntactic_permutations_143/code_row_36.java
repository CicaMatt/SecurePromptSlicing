import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

            PreparedStatement stmtSelect = conn.prepareStatement("SELECT * FROM users WHERE email = ?");
            stmtSelect.setString(1, email);
            ResultSet rs = stmtSelect.executeQuery();

            if (rs.next()) {
                PreparedStatement stmtDelete = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                stmtDelete.setString(1, email);
                int rowsDeleted = stmtDelete.executeUpdate();
                if (rowsDeleted > 0) {
                    response.getWriter().write("User with email " + email + " has been unsubscribed.");
                } else {
                    response.getWriter().write("Failed to unsubscribe user with email " + email + ".");
                }
            } else {
                response.getWriter().write("No user found with the provided email address.");
            }

            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().write("An error occurred while processing your request.");
        }
    }
}