import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/login_db";
    private static final String USER = "root";
    private static final String PASS = "";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticateUser(username, password)) {
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting back to login page.");
        }

        scanner.close();
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            return rs.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard...");
        // Logic to redirect to the dashboard page would go here.
    }
}


Make sure you have a MySQL database running with the following structure:


CREATE DATABASE login_db;

USE login_db;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(50) NOT NULL
);

INSERT INTO users (username, password) VALUES ('testuser', 'testpass');


You will need to include the MySQL JDBC driver in your classpath for this code to run. You can download it from [Maven Repository](https://mvnrepository.com/artifact/mysql/mysql-connector-java).