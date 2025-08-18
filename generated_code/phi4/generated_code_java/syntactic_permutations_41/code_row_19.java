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
    public String getInfo(@RequestParam(defaultValue = "user@example.com") String email,
                          @RequestParam(defaultValue = "0000") String ssnLastFour) {
        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>" +
                "</body></html>";
    }
}


To make this application runnable, you'll need to set up a Spring Boot project. Here are the steps:

1. **Set Up Project**: Use Spring Initializr (https://start.spring.io/) to generate a Maven or Gradle project with the "Spring Web" dependency.

2. **Add Code**: Replace the generated `Application.java` and any controller files with the code above.

3. **Run Application**: Execute the application using your IDE or from the command line with `mvn spring-boot:run` (for Maven) or `gradle bootRun` (for Gradle).

4. **Access**: Visit `http://localhost:8080/info?email=user@example.com&ssnLastFour=1234` in a web browser to see the output. Adjust parameters as needed.