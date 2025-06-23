import java.sql.*;
import java.util.Scanner;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
    private static final String DB_URL = "jdbc:mysql://localhost/test";
    private static final String USER = "root";
    private static final String PASS = "password123";
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String userName = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String passWord = scanner.nextLine();
        
        System.out.print("Enter first name: ");
        String firstName = scanner.nextLine();
        
        System.out.print("Enter last name: ");
        String lastName = scanner.nextLine();
        
        System.out.print("Enter email address: ");
        String email = scanner.nextLine();
        
        try {
            Class.forName(JDBC_DRIVER);
            
            Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
            Statement statement = connection.createStatement();
            
            String query = "SELECT user_name FROM users WHERE user_name = '" + userName + "'";
            ResultSet resultSet = statement.executeQuery(query);
            
            if (resultSet.next()) {
                System.out.println("The username already exists");
            } else {
                MessageDigest digest = null;
                
                try {
                    digest = MessageDigest.getInstance("SHA-256");
                } catch (NoSuchAlgorithmException e) {
                    System.out.println("Error: " + e);
                } 
                
                byte[] encodedhash = digest.digest(passWord.getBytes());
                String hashPass = bytesToHex(encodedhash);
            
                query = "INSERT INTO users (user_name, password, first_name, last_name, email) VALUES ('" + userName 
                    + "', '" + hashPass + "', '" + firstName + "', '" + lastName + "', '" + email + "')";
                    
                statement.executeUpdate(query);
            
                System.out.println("Registration successful");
            }
        } catch (SQLException | ClassNotFoundException e) {
            System.out.println("Error: " + e);
        }
    }
    
    private static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder();
        
        for (int i = 0; i < hash.length; i++) {
            String hex = Integer.toHexString(0xff & hash[i]);
            
            if (hex.length() == 1) {
                hexString.append('0');
            }
            
            hexString.append(hex);
        }
        
        return hexString.toString();
    }
}