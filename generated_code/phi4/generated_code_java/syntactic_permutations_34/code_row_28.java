import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/login_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "testUser"; // Simulated user input
        String password = "testPass"; // Simulated user input

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect user to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting back to Login Page...");
        // Code to redirect user back to the login page
    }
}



-- SQL script for creating database and table

CREATE DATABASE IF NOT EXISTS login_db;

USE login_db;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(50) NOT NULL
);

INSERT INTO users (username, password) VALUES ('testUser', 'testPass');


**Note:** Replace `DB_URL`, `USER`, and `PASS` with your actual database connection details. Ensure that the MySQL JDBC driver is included in your project's classpath.