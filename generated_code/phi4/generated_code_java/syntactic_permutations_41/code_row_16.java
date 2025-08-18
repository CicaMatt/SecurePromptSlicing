import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo(@RequestParam("username") String username,
                          @RequestParam("email") String email,
                          @RequestParam("ssn") String ssn) {
        
        if (ssn.length() < 4) {
            return "Invalid SSN. Last 4 digits required.";
        }

        return "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>"
                + "</body></html>";
    }
}


This code uses Spring Boot to create a simple web application. It defines a single route `/info` that accepts `username`, `email`, and `ssn` as query parameters and returns an HTML page displaying the requested information. Make sure you have Spring Boot dependencies configured in your build system (like Maven or Gradle) to run this code.