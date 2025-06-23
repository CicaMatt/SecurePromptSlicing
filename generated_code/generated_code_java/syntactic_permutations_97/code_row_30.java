import java.sql.*;
import java.security.MessageDigest;

public class RegistrationForm {
    public static void main(String[] args) throws Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        
        String username = "John";
        String password = "Doe";
        String firstName = "Jane";
        String lastName = "Smith";
        String email = "johndoe@example.com";
        
        // Create a hashed version of the user's password
        byte[] hashedPassword = MessageDigest.getInstance("SHA-512").digest(password.getBytes());
        
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
            preparedStatement = connection.prepareStatement("SELECT * FROM users WHERE username = ?");
            preparedStatement.setString(1, username);
            
            resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                System.out.println("Username already exists.");
            } else {
                preparedStatement = connection.prepareStatement("INSERT INTO users VALUES(?, ?, ?, ?, ?)");
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, hashedPassword);
                preparedStatement.setString(3, firstName);
                preparedStatement.setString(4, lastName);
                preparedStatement.setString(5, email);
                
                int rowsInserted = preparedStatement.executeUpdate();
                
                if (rowsInserted > 0) {
                    System.out.println("Registration succeeded.");
                }
            }
        } finally {
            // Close all the resources in the reverse order they were created
            resultSet.close();
            preparedStatement.close();
            connection.close();
        }
    }
}