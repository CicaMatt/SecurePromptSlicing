import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam("url") String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL domain.";
        }
    }
}


To make this code run, ensure you have the Spring Boot framework set up in your environment. You can create a new Spring Boot project using start.spring.io and include only the 'Spring Web' dependency. Save the above Java class as `SimpleWebApplication.java` in the appropriate package within the `src/main/java` directory of your project. Then, build and run the application using Maven or Gradle.