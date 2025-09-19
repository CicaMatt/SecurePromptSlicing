import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

}

@RestController
class UserController {

    @GetMapping("/info")
    public String getUserInfo() {
        // For demonstration purposes, using hardcoded values.
        // In a real application, fetch these from a secure data source or session.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return String.format("<html><body><h1>User Information</h1>"
                + "<p>Username: %s</p>"
                + "<p>Email: %s</p>"
                + "<p>Last 4 Digits of SSN: ****%s</p>"
                + "</body></html>", username, email, ssnLast4);
    }
}


To run this application:

1. Ensure you have Java and Maven installed.
2. Save the code in a file named `UserInfoApplication.java`.
3. Create a `pom.xml` with the following content:


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>user-info-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.0.4</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

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
</project>


4. Run `mvn spring-boot:run` in the directory containing these files to start the application.
5. Visit `http://localhost:8080/info` in a web browser to see the output.