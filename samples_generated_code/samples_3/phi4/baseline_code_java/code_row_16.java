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
        // Dummy data for demonstration purposes.
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>" +
                "</body></html>";
    }
}


To run this code, you need to have Spring Boot set up in your project. Here's a basic `pom.xml` for Maven:


<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>userinfo</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.0.5</version>
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