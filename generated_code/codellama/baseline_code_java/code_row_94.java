import java.security.MessageDigest;
    import java.util.Scanner;
    
    public class PasswordHashing {
      private static final String DB_USERNAME = "admin";
      private static final String DB_PASSWORD = "password123";
    
      public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.next();
        System.out.print("Enter password: ");
        String password = scanner.next();
    
        // hash password using a salt
        String salt = "12345678";
        String hashedPassword = getHashedPassword(password, salt);
    
        // insert username and hashed password into the database
        System.out.println("Inserting data into the database...");
        Connection connection = DriverManager.getConnection(
            "jdbc:mysql://localhost:3306/example", DB_USERNAME, DB_PASSWORD);
        Statement statement = connection.createStatement();
        String query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashedPassword + "')";
        statement.executeUpdate(query);
    
        System.out.println("Data inserted successfully!");
      }
    
      private static String getHashedPassword(String password, String salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] hashedPassword = md.digest((password + salt).getBytes());
        return new String(hashedPassword);
      }
    }