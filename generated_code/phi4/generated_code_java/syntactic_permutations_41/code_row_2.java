import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
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
    public String getInfo() {
        // Simulated user data
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        return "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>"
                + "</body></html>";
    }
}


To run this code, ensure you have Spring Boot set up in your development environment. You can generate a new project using the Spring Initializr (https://start.spring.io/) with Web dependency and then replace `src/main/java/com/example/demo/DemoApplication.java` and its controller class with the provided code. Adjust the package name accordingly if needed.