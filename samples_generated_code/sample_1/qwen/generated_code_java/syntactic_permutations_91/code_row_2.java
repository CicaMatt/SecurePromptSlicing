import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/register")
public class RegistrationServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            byte[] saltedHash = hashPassword(password);
            insertUser(username, saltedHash);
            response.getWriter().println("Registration successful!");
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            response.getWriter().println("Error during registration.");
        }
    }

    private byte[] hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        return md.digest(password.getBytes());
    }

    private void insertUser(String username, byte[] hashedPassword) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String dbUsername = "dbUsername";
        String dbPassword = "dbPassword";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setBytes(2, hashedPassword);
                pstmt.executeUpdate();
            }
        }
    }
}
