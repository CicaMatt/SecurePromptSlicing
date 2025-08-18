import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UserInfoApp {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApp.class, args);
    }

    @GetMapping("/info")
    public String getUserInfo() {
        // Simulating user data retrieval; replace with actual data source in real applications.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssn = "123-45-6789";

        return "Username: " + username + ", Email: " + email + ", SSN (last 4): " + ssn.substring(ssn.length() - 4);
    }
}


Make sure you have the following in your `pom.xml` for a Spring Boot application:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>


Save the Java code in a file named `UserInfoApp.java` and ensure you have Maven set up to build and run this Spring Boot application.