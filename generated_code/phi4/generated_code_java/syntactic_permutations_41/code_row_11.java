import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }

    @GetMapping("/info")
    public String getUserInfo() {
        // Simulated user data
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>" +
                "</body></html>";
    }
}


Make sure to include the following in your `pom.xml` if you are using Maven:


<dependencies>
    
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>


For Gradle, include in your `build.gradle`:




tasks.named('test') {
    useJUnitPlatform()
}