import java.security.MessageDigest;
import java.sql.*;

public class UserRegistration {

    private String username; // Username of user
    private String password; // Password of user

    public void setUsername(String username) { // Method to set the username of a user
        this.username = username;
    }

    public void setPassword(String password) { // Method to set the password of a user
        this.password = password;
    }

    public String getUsername() { // Method to get the username of a user
        return username;
    }

    public String getPassword() { // Method to get the hashed password of a user
        return password;
    }

    public static void main(String[] args) throws Exception {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");

        Statement stmt = conn.createStatement();

        UserRegistration user = new UserRegistration(); // Create a new instance of the UserRegistration class

        System.out.println("Enter username: ");
        String userName = scanner.nextLine();
        user.setUsername(userName); // Set the username of the user

        System.out.println("Enter password: ");
        String passWord = scanner.nextLine();
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        md5.update(passWord.getBytes());
        byte[] digest = md5.digest();
        String password = new String(digest);
        user.setPassword(password); // Set the hashed password of the user

        stmt.executeUpdate("INSERT INTO users (username, password) VALUES ('" + user.getUsername() + "', '" + user.getPassword()
                + "')");

        System.out.println("User registered successfully!");
    }
}