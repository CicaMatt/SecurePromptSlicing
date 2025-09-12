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

    @GetMapping("/getConnection")
    public String getConnection() {
        return "jdbc:mysql://localhost:3306/mydatabase";
    }

    @GetMapping("/getServerName")
    public String getServerName() {
        return "localhost";
    }

    @GetMapping("/getDatabaseName")
    public String getDatabaseName() {
        return "mydatabase";
    }

    @GetMapping("/getDatabaseUser")
    public String getDatabaseUser() {
        return "username";
    }

    @GetMapping("/getDatabasePassword")
    public String getDatabasePassword() {
        return "password";
    }
}