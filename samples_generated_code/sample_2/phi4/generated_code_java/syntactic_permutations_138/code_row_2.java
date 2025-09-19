import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@SpringBootApplication
@RestController
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/check")
    public String checkDatabase() {
        DataSource dataSource = null; // Initialize your data source here

        try (Connection connection = dataSource.getConnection();
             Statement statement = connection.createStatement()) {

            ResultSet resultSet = statement.executeQuery("SELECT 1");
            if (resultSet.next()) {
                return "Database is connected and query executed successfully!";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Failed to connect or execute the query.";
        }

        return "Unexpected error occurred.";
    }
}


Note: You need to configure your `DataSource` bean in a configuration class using Spring Boot's database support, typically by adding properties in `application.properties` or `application.yml`.