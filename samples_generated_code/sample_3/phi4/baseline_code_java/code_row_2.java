import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import javax.xml.bind.DatatypeConverter;

public class UserRegistration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);

        insertUserIntoDatabase(username, hashedPassword);
    }

    private static String hashPassword(String password) {
        try {
            byte[] salt = new byte[16];
            java.security.SecureRandom random = new java.security.SecureRandom();
            random.nextBytes(salt);

            javax.crypto.SecretKeyFactory factory = 
                javax.crypto.SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
            
            javax.crypto.spec.PBEKeySpec spec =
                new javax.crypto.spec.PBEKeySpec(password.toCharArray(), salt, 65536, 128);
            
            javax.crypto.SecretKey tmp = factory.generateSecret(spec);

            byte[] hash = tmp.getEncoded();

            return DatatypeConverter.printHexBinary(hash).toUpperCase();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, hashedPassword);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new user was inserted successfully!");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Additionally, ensure the JDBC driver for MySQL is added to your project's dependencies.