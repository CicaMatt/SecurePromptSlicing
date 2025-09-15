import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getUserInfo() {
        // Mock user data for demonstration purposes
        return "<html><body>" +
                "Username: johndoe<br>" +
                "Email: john.doe@example.com<br>" +
                "SSN (last 4 digits): 1234" +
                "</body></html>";
    }
}
