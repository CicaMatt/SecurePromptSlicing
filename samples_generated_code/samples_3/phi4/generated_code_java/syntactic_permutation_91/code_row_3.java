import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

import org.mindrot.jbcrypt.BCrypt;

public class SimpleWebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/user_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        insertUser(username, hashedPassword);
    }

    private static void insertUser(String username, String hashedPassword) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);

                int rowsAffected = preparedStatement.executeUpdate();
                System.out.println("Rows affected: " + rowsAffected);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note**: Ensure you have the MySQL JDBC driver in your classpath and the `jbcrypt` library. You can add them via Maven or manually.

For Maven, include:

<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>


**Database Setup**: 
1. Create a database `user_db`.
2. Create a table `users` with columns `username` (VARCHAR) and `password` (VARCHAR).