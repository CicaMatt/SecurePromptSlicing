import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
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
    public String getInfo() {
        // Sample user data; in a real application, this would be retrieved from a database or other secure source.
        String username = "JohnDoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return String.format("Username: %s<br>Email: %s<br>Last 4 Digits of SSN: ****%s", 
                             username, email, ssnLast4);
    }
}


To make this code runnable:

1. Create a new Spring Boot project using [Spring Initializr](https://start.spring.io/).
2. Choose the following dependencies:
   - `Spring Web`
3. Add the above Java classes to your project.
4. Run the application by executing the main method in the `InfoApplication` class.

This will start a web server, and you can access the `/info` endpoint at `http://localhost:8080/info`.