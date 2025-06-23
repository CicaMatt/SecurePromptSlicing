import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.*;

public class Registration {
    public static void main(String[] args) throws NoSuchAlgorithmException, SQLException {
        String username = "admin";
        String password = "password123"; // hash this before inserting into database
        String firstName = "John";
        String lastName = "Smith";
        String email = "johnsmith@email.com";

        // hash the password
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());
        String hashedPass = new String(hashedPassword);

        // check if username is in the database
        boolean userExists = false;
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb",
                "root", "password");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "'");
        if (rs.next()) {
            userExists = true;
            System.out.println("Username already exists.");
        } else {
            // insert the username and hashed password into the database
            String sql = "INSERT INTO users(username, password, first_name, last_name, email)" +
                    "VALUES ('" + username + "', '" + hashedPass + "', '" + firstName + "', '" + lastName + "', '" + email + "')";
            stmt.executeUpdate(sql);
            System.out.println("Registration successful.");
        }

    }
}