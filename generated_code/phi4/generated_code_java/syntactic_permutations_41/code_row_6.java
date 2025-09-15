import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @GetMapping("/info")
    public String userInfo() {
        // Simulating user data retrieval
        String username = "JohnDoe";
        String email = "john.doe@example.com";
        String ssnLast4Digits = "1234";

        return String.format("Username: %s<br>Email: %s<br>SSN (last 4): %s", username, email, ssnLast4Digits);
    }
}


Make sure you have the necessary Spring Boot dependencies in your `pom.xml` if you are using Maven:


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


Or in your `build.gradle` if you are using Gradle:




bootJar {
    mainClassName = 'UserInfoApplication'
}
