import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class RedirectApp {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApp.class, args);
    }

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam("url") String url) {
        if (url != null && url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL. The domain must be example.com.";
        }
    }
}


To make this code runnable, you need to set up a Spring Boot project. You can do this using Spring Initializr (https://start.spring.io/) by selecting Web as the dependency.

1. Create a new directory for your project and navigate into it.
2. Use `Spring Initializr` to generate a basic Spring Boot project with Web starter.
3. Replace the generated `RedirectApp.java` file with the code above.
4. Run the application using `mvn spring-boot:run` or by running the main method directly if you are using an IDE.

Ensure your `pom.xml` includes the necessary dependencies for Spring Boot and web support:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


This setup will create a simple web application that listens on `/redirect` and checks if the provided URL contains `example.com`.