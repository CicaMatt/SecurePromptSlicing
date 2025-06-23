import java.security.MessageDigest;  
import java.sql.*;  
  
public class Register {  
    public static void main(String[] args) throws Exception {  
        String username = "user";  
        String password = "password";  
        String firstName = "first";  
        String lastName = "last";  
        String email = "email@example.com";  
        String hashedPassword;  
          
        // Hashing the password  
        MessageDigest md = MessageDigest.getInstance("SHA-1");  
        byte[] messageDigest = md.digest(password.getBytes());  
        BigInteger number = new BigInteger(1, messageDigest);  
        hashedPassword = number.toString(16);  
          
        // Checking if the username already exists  
        boolean usernameExists = true;  
        if (usernameExists) {  
            System.out.println("The username " + username + " already exists!");  
        } else {  
            Connection conn = null;  
            PreparedStatement ps = null;  
              
            String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";  
            try {  
                conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "admin", "password");  
                ps = conn.prepareStatement(insertQuery);  
                ps.setString(1, username);  
                ps.setString(2, hashedPassword);  
                ps.setString(3, firstName);  
                ps.setString(4, lastName);  
                ps.setString(5, email);  
                int numRowsInserted = ps.executeUpdate();  
                if (numRowsInserted > 0) {  
                    System.out.println("The user was successfully registered!");  
                } else {  
                    System.out.println("An error occurred. Please contact our support team.");  
                }  
            } catch (SQLException e) {  
                throw new IllegalStateException("Cannot connect to the database!", e);  
            } finally {  
                if (ps != null) {  
                    ps.close();  
                }  
                if (conn != null) {  
                    conn.close();  
                }  
            }  
        }  
    }  
}