import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        registerUser(username, password);
        
        scanner.close();
    }

    private static void registerUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, password);

                int rowsAffected = pstmt.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("User registered successfully!");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath. You can include it by adding a dependency if you are using Maven:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.28</version> <!-- Use the latest version available -->
</dependency>


Or by downloading the JAR and adding it to your project's libraries if you're not using Maven.