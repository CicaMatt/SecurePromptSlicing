import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getUserInfo() {
        // Mock user data for demonstration purposes
        return "<html><body>" +
                "Username: johndoe<br>" +
                "Email: john.doe@example.com<br>" +
                "SSN (last 4 digits): 1234" +
                "</body></html>";
    }
}


**Note:** To run this code, you need to have Spring Boot set up in your project. You can create a new Maven or Gradle project and add the following dependency for Spring Web:

For Maven, include in `pom.xml`:

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>


For Gradle, include in `build.gradle`:

dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}


Compile and run the application using your IDE or command line tools like Maven (`mvn spring-boot:run`) or Gradle (`gradlew bootRun`).