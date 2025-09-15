import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/dbConnection")
    public Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
    }

    @GetMapping("/serverName")
    public String getServerName() {
        return "Localhost";
    }

    @GetMapping("/dbName")
    public String getDatabaseName() {
        return "mydatabase";
    }

    @GetMapping("/dbUser")
    public String getDatabaseUser() {
        return "root";
    }

    @GetMapping("/dbPassword")
    public String getDatabasePassword() {
        return "password"; // In a real application, use environment variables or secure vaults.
    }
}
