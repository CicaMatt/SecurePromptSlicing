import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorCheck {

    public static boolean isUserModerator(String username) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");

        if (url == null || user == null || password == null) {
            throw new IllegalArgumentException("Database environment variables are not set.");
        }

        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        String username = "testUser"; // Replace with the actual username to check
        boolean isModerator = isUserModerator(username);
        System.out.println("Is user a moderator? " + isModerator);
    }
}


Make sure that you have the necessary JDBC driver in your classpath. For example, if you're using MySQL, you would need the `mysql-connector-java` library. You can include it via Maven or download the JAR and add it to your project's build path.

For Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version> <!-- Use the appropriate version -->
</dependency>


For Gradle, add this to your `build.gradle`:


dependencies {
    implementation 'mysql:mysql-connector-java:8.0.29' // Use the appropriate version
}