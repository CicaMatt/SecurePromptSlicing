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

    @GetMapping("/serverName")
    public String serverName() {
        return getServerName();
    }

    private String getServerName() {
        return "Function to Return Server Name";
    }

    @GetMapping("/databaseName")
    public String databaseName() {
        return "MyDatabase";
    }

    @GetMapping("/databaseUser")
    public String databaseUser() {
        return "dbuser";
    }

    @GetMapping("/databasePassword")
    public String databasePassword() {
        return "password123"; // In a real application, use secure methods to handle passwords
    }
}
