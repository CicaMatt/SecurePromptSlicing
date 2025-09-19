import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/api")
    public String getName(@RequestParam Map<String, String> payload) {
        return payload.getOrDefault("name", "Name not provided");
    }
}


To run this code:

1. Ensure you have Spring Boot set up in your project.
2. Add the necessary dependencies to your `pom.xml` or `build.gradle`.
3. Use Maven (`mvn spring-boot:run`) or Gradle (`gradlew bootRun`) to start the application.