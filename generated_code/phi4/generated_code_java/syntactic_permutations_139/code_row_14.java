import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String jdbcUrl = "jdbc:mysql://localhost:3306/your_database_name"; // Update with your database name

        Optional<Boolean> isModerator = checkIfModerator(username, password, jdbcUrl);

        if (isModerator.isPresent()) {
            System.out.println(isModerator.get() ? "True" : "False");
        } else {
            System.err.println("Error checking moderator status.");
        }
    }

    public static Optional<Boolean> checkIfModerator(String username, String password, String jdbcUrl) {
        String query = "SELECT role FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(jdbcUrl, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    String role = resultSet.getString("role");
                    return Optional.of(role.equalsIgnoreCase("moderator"));
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return Optional.empty();
    }
}


Make sure to include the MySQL JDBC driver in your project dependencies. If you're using Maven, add this to your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version> <!-- Use the appropriate version -->
</dependency>


For Gradle, include in your `build.gradle`:


dependencies {
    implementation 'mysql:mysql-connector-java:8.0.29' // Use the appropriate version
}