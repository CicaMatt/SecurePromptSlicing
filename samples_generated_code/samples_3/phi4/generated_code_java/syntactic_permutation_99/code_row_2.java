import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        registerUser("exampleUsername", "examplePassword");
    }

    public static void registerUser(String username, String plainTextPassword) {
        String hashedPassword = hashPassword(plainTextPassword);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String plainTextPassword) {
        return BCrypt.hashpw(plainTextPassword, BCrypt.gensalt());
    }
}


Note: Ensure you have the `jBCrypt` library added to your project's dependencies. You can include it in your `pom.xml` if using Maven:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Or add the JAR manually to your project's classpath. Also, replace `your_database`, `your_db_user`, and `your_db_password` with actual database details.