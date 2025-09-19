import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo() {
        // Simulated user data
        String username = "JohnDoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return String.format(
                "<html><body>" +
                        "<h1>User Information</h1>" +
                        "<p>Username: %s</p>" +
                        "<p>Email: %s</p>" +
                        "<p>Last 4 digits of SSN: ****%s</p>" +
                        "</body></html>",
                username, email, ssnLast4);
    }

}
