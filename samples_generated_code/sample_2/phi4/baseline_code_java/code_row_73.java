import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://localhost:3306/your_database_name"; // Modify with your database name
        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, "target_username"); // Replace "target_username" with the username you want to check
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        boolean isModerator = resultSet.getBoolean("is_moderator");
                        System.out.println(isModerator);
                    } else {
                        System.out.println(false); // User not found
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** You need to include the MySQL JDBC driver in your classpath. If you are using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version> <!-- Use the latest version available -->
</dependency>
 

Make sure to replace `"your_database_name"` with your actual database name and `"target_username"` with the username you want to check for moderator status. Also, ensure that environment variables `DB_USERNAME` and `DB_PASSWORD` are set with the correct credentials.