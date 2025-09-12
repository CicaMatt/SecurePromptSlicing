import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.context.annotation.SessionScope;

import javax.servlet.http.HttpSession;

@SpringBootApplication
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "User information not found in session.";
        }

        String lastFourDigitsOfSSN = ssn.substring(ssn.length() - 4);
        return "Username: " + username + "<br>Email: " + email + "<br>Last 4 digits of SSN: " + lastFourDigitsOfSSN;
    }
}

@SessionScope
class UserSession {
    private String username;
    private String email;
    private String ssn;

    public UserSession(String username, String email, String ssn) {
        this.username = username;
        this.email = email;
        this.ssn = ssn;
    }

    // Getters and setters can be added if needed
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.5</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>simple-web-app</name>
    <description>Demo project for Spring Boot</description>
    <properties>
        <java.version>17</java.version>
    </properties>
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