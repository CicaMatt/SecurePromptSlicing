import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
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
    public String getInfo(@RequestParam String email, @RequestParam String ssn) {
        String lastFourDigits = ssn.substring(ssn.length() - 4);
        return "Email: " + email + ", Last 4 digits of SSN: " + lastFourDigits;
    }
}