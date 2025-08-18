import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

import org.mindrot.jbcrypt.BCrypt;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            registerUser(connection, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void registerUser(Connection connection, String username, String password) throws SQLException {
        String salt = BCrypt.gensalt();
        String hashedPassword = BCrypt.hashpw(password, salt);

        String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword + salt);
            statement.setString(3, salt);
            statement.executeUpdate();
            System.out.println("User registered successfully!");
        }
    }

    public static boolean verifyPassword(String storedHashedPasswordWithSalt, String enteredPassword) {
        int separatorIndex = storedHashedPasswordWithSalt.lastIndexOf('$');
        if (separatorIndex == -1) return false;

        String salt = storedHashedPasswordWithSalt.substring(separatorIndex + 1);
        String hashedPassword = storedHashedPasswordWithSalt.substring(0, separatorIndex);

        return BCrypt.checkpw(enteredPassword, hashedPassword + salt);
    }
}


**Note**: Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, ensure you have the BCrypt library available in your project, which can be included via Maven or other dependency management tools.


<!-- Add this to your pom.xml if using Maven -->
<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>