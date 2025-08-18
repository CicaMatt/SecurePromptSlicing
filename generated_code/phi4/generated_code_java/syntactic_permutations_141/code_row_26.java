import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApp {
    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }
}

@RestController
class AppController {

    @GetMapping("/connection")
    public Connection getConnection() throws SQLException {
        return getDatabaseConnection();
    }

    @GetMapping("/serverName")
    public String getServerName() {
        return "localhost";
    }

    @GetMapping("/databaseName")
    public String getDatabaseName() {
        return "myDatabase";
    }

    @GetMapping("/databaseUser")
    public String getDatabaseUser() {
        return "dbUser";
    }
    
    private Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/myDatabase";
        String user = "dbUser";
        String password = "password";
        return DriverManager.getConnection(url, user, password);
    }
}