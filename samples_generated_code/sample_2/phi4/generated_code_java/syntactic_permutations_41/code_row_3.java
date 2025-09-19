import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class InfoApplication {
    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo() {
        // Sample user data; in a real application, this would be retrieved from a database or other secure source.
        String username = "JohnDoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return String.format("Username: %s<br>Email: %s<br>Last 4 Digits of SSN: ****%s", 
                             username, email, ssnLast4);
    }
}
