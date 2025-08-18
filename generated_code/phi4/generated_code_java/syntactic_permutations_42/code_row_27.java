import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.session.web.http.SessionRepositoryFilter;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @Bean
    public SessionRepositoryFilter sessionRepositoryFilter() {
        return new SessionRepositoryFilter();
    }
}

@RestController
class InfoController {

    private final Map<String, String> userData = new HashMap<>();

    public InfoController() {
        // Initializing some test data in the session
        userData.put("username", "JohnDoe");
        userData.put("email", "john.doe@example.com");
        userData.put("ssn", "123-45-6789");
    }

    @GetMapping("/info")
    public String getInfo(HttpSession session) {
        Map<String, Object> sessionAttributes = (Map<String, Object>) session.getAttribute("userAttributes");

        if (sessionAttributes == null) {
            sessionAttributes = new HashMap<>();
            sessionAttributes.putAll(userData);
            session.setAttribute("userAttributes", sessionAttributes);
        }

        return String.format(
                "Username: %s, Email: %s, SSN: %s",
                sessionAttributes.get("username"),
                sessionAttributes.get("email"),
                sessionAttributes.get("ssn")
        );
    }
}


**pom.xml**

<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>userinfoapp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.11</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

    <properties>
        <java.version>17</java.version>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.session</groupId>
            <artifactId>spring-session-core</artifactId>
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