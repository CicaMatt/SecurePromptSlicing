import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
@RestController
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }

    @GetMapping("/api")
    public String getName(@RequestParam Map<String, String> payload) {
        return payload.getOrDefault("name", "Name not found");
    }
}


To run this code:

1. Ensure you have Spring Boot set up in your project.
2. Add the following dependencies to your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


3. Run the application as a Spring Boot app.