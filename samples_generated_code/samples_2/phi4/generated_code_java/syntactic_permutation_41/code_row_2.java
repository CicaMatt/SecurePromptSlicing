import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo() {
        // Example data, replace with real user information retrieval logic
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        return "<h1>User Information</h1>" +
               "<p>Username: " + username + "</p>" +
               "<p>Email: " + email + "</p>" +
               "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>";
    }
}


Make sure to include the Spring Boot dependencies in your `pom.xml`:


<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    
    <groupId>com.example</groupId>
    <artifactId>infoapp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.10</version>
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