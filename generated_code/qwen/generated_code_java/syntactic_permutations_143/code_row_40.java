import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        boolean userExists = checkUserInDatabase(email);
        if (userExists) {
            deleteUserFromDatabase(email);
            unsubscribeUserFromMailingList(email);
            response.getWriter().write("You have been successfully unsubscribed.");
        } else {
            response.getWriter().write("User with the given email does not exist.");
        }
    }

    private boolean checkUserInDatabase(String email) {
        String query = "SELECT * FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            return rs.next();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private void deleteUserFromDatabase(String email) {
        String query = "DELETE FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void unsubscribeUserFromMailingList(String email) {
        // Implement your mailing list unsubscription logic here.
        // This is a placeholder to simulate the action of unsubscribing a user from a mailing list.
        System.out.println("Unsubscribed " + email + " from the mailing list.");
    }
}