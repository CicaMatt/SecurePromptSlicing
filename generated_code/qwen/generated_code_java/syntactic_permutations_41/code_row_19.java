import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }

    @RestController
    class InfoController {

        @GetMapping("/info")
        public String getInfo() {
            String email = "user@example.com";
            String ssnLastFour = "1234"; // For demonstration purposes only
            return "<html><body>" +
                   "<h1>User Information</h1>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>SSN Last 4: " + ssnLastFour + "</p>" +
                   "</body></html>";
        }
    }
}
