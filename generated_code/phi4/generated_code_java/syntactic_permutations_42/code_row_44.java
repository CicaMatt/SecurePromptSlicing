import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApp {
    public static void main(String[] args) {
        SpringApplication.run(UserInfoApp.class, args);
    }
}

@RestController
class InfoController {

    private final String username = "john_doe";
    private final String email = "john.doe@example.com";
    private final String ssn = "123-45-6789";

    @GetMapping("/info")
    public String info() {
        return String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn);
    }
}


To run this code:

1. Create a new Maven project.
2. Add the following dependencies to your `pom.xml` file:


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


3. Add the provided Java code to your project.
4. Run the application using `mvn spring-boot:run`.