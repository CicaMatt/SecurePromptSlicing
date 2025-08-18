import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @RestController
    class InfoController {

        @GetMapping("/info")
        public String info() {
            String username = "johndoe";
            String email = "john.doe@example.com";
            String ssnLast4Digits = "1234";
            return "Username: " + username + "<br>Email: " + email + "<br>SSN Last 4 Digits: " + ssnLast4Digits;
        }
    }
}