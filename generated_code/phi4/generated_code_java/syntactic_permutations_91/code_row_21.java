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
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            try {
                // Hash the password
                String hashedPassword = hashPassword(password);

                // Insert user into database
                insertUser(username, hashedPassword);
                
                response.getWriter().write("Registration successful!");
            } catch (Exception e) {
                response.getWriter().write("Error during registration: " + e.getMessage());
            }
        } else {
            response.getWriter().write("Username and password are required.");
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());

        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }

        return sb.toString();
    }

    private void insertUser(String username, String hashedPassword) throws SQLException, ClassNotFoundException {
        // Database configuration
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String dbUsername = "root";
        String dbPassword = "";

        Class.forName("com.mysql.cj.jdbc.Driver");
        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";

            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                statement.executeUpdate();
            }
        }
    }
}


**Note:** 
- You need to configure the database URL (`url`), username (`dbUsername`), and password (`dbPassword`) according to your setup.
- Ensure that you have a `users` table in your database with columns `username` and `password`.
- The MySQL Connector/J driver should be included in your project's dependencies.