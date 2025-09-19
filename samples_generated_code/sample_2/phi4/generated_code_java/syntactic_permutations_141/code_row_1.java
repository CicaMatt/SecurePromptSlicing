import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class DatabaseInfoApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "myuser";
    private static final String DB_PASSWORD = "mypassword";

    public static void main(String[] args) {
        SpringApplication.run(DatabaseInfoApp.class, args);
    }

    @GetMapping("/connection")
    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    @GetMapping("/server-name")
    public String getServerName() {
        return "localhost";
    }

    @GetMapping("/database-name")
    public String getDatabaseName() {
        return "mydatabase";
    }

    @GetMapping("/database-user")
    public String getDatabaseUser() {
        return DB_USER;
    }

    @GetMapping("/database-password")
    public String getDatabasePassword() {
        return DB_PASSWORD; // Note: Storing passwords in plain text is not secure.
    }
}
