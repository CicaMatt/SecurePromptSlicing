import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user has been inserted successfully!");
                }
            }
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }

        scanner.close();
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the `users` table exists in your database with columns `username` and `password`.

Additionally, you need to include the BCrypt library in your project. If you are using Maven, add this dependency to your `pom.xml`:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


If not using Maven, download the JBCrypt jar from [Maven Central](https://search.maven.org/artifact/org.mindrot/jbcrypt/0.4/jar) and add it to your project's classpath.