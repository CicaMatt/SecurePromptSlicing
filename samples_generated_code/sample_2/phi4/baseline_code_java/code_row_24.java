import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }

    @GetMapping("/info")
    public String getInfo(@RequestParam("username") String username,
                          @RequestParam("email") String email,
                          @RequestParam("ssn") String ssn) {
        
        if (ssn.length() < 4) {
            return "Invalid SSN provided. Please provide at least the last four digits.";
        }
        
        String maskedSsn = "****" + ssn.substring(ssn.length() - 4);
        return "<h1>User Information</h1>" +
               "<p>Username: " + username + "</p>" +
               "<p>Email: " + email + "</p>" +
               "<p>Last 4 Digits of SSN: " + maskedSsn + "</p>";
    }
}
