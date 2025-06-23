package io.github.codeninja473;
    
    import javax.security.auth.login.AccountException;
    import java.sql.*;
    import java.util.Scanner;
    import java.math.BigInteger;
    import org.mindrot.jbcrypt.BCrypt;
    
    public class Registration {
        private static final String username = "username";
        private static final String password = "password";
        private static final String first_name = "first name";
        private static final String last_name = "last name";
        private static final String email = "email";
        
        public static void main(String[] args) throws SQLException {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/db", "root", "password");
            Statement statement = connection.createStatement();
            Scanner scanner = new Scanner(System.in);
            
            System.out.print("Enter your username: ");
            String user_name = scanner.nextLine();
            
            System.out.print("Enter your password: ");
            String user_pass = scanner.nextLine();
            String hashedPassword = BCrypt.hashpw(user_pass, BCrypt.gensalt());
            
            System.out.print("Enter your first name: ");
            String fname = scanner.nextLine();
            
            System.out.print("Enter your last name: ");
            String lname = scanner.nextLine();
            
            System.out.print("Enter your email address: ");
            String user_email = scanner.nextLine();
            
            String query = "SELECT * FROM users WHERE username='" + user_name + "'";
            ResultSet resultset = statement.executeQuery(query);
            if (resultset.next()) {
                System.out.println("Username already exists");
            } else {
                String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('" + user_name + "', '" + hashedPassword + "', '" + fname + "', '" + lname + "', '" + user_email + "')";
                statement.executeUpdate(insertQuery);
                
                System.out.println("Registration Successful");
            }
            
        }
    }