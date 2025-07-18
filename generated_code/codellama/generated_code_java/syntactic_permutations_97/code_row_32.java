// Import all required libraries for database connectivity
import java.sql.*;

public class RegistrationForm {
    // Create a connection to your MySQL Database
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", "root", "");
    Statement statement = null;
    
    public static void main(String[] args) {
        // Get input for username and password
        String username = getInput("username");
        String password = getInput("password");
        // Check if the username already exists in the database
        if (checkIfUsernameExists(conn, statement, username)) {
            System.out.println("The username already exists.");
        } else {
            // If it doesn't exist, hash the password and insert into the database
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            insertIntoDatabase(conn, statement, username, hashedPassword);
            System.out.println("Registration successful.");
        }
    }
    
    // Function to check if the username already exists in the database
    public static boolean checkIfUsernameExists(Connection conn, Statement statement, String username) {
        try {
            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE username = " + username);
            return !rs.next(); // If there is no result, it means the username doesn't exist
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
    
    // Function to insert into the database
    public static void insertIntoDatabase(Connection conn, Statement statement, String username, String hashedPassword) {
        try {
            statement = conn.createStatement();
            String sql = "INSERT INTO users (username, password) VALUES (" + username + ", " + hashedPassword + ")";
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}