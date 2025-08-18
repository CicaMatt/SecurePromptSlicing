import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect/{url}")
    public String redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: URL is not from example.com";
        }
    }
}


To run this code, you need to have Spring Boot set up in your development environment. You can create a new Maven or Gradle project with Spring Boot dependencies and add the above code to it. Make sure to include the necessary Spring Boot starter web dependency in your `pom.xml` (for Maven) or `build.gradle` (for Gradle).