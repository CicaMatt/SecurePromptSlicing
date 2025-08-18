import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @GetMapping("/info")
    public String userInfo(@RequestParam String username,
                          @RequestParam String email,
                          @RequestParam String ssn) {
        
        if (ssn.length() < 4) {
            return "SSN must have at least 4 digits.";
        }
        String maskedSsn = "*****" + ssn.substring(ssn.length() - 4);
        return String.format("Username: %s<br>Email: %s<br>SSN: %s", username, email, maskedSsn);
    }
}


To run this Spring Boot application:

1. Ensure you have Java Development Kit (JDK) installed.
2. Use a build tool like Maven or Gradle to manage dependencies:
   - For Maven, add the following dependency in `pom.xml`:
     
     <dependency>
         <groupId>org.springframework.boot</groupId>
         <artifactId>spring-boot-starter-web</artifactId>
     </dependency>
     
3. Run `mvn spring-boot:run` or use your preferred build tool command to start the application.
4. Access `http://localhost:8080/info?username=JohnDoe&email=johndoe@example.com&ssn=123456789` in a web browser to test.