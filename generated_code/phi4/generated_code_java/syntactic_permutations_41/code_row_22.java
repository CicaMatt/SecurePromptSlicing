import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;

@SpringBootApplication
@RestController
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }

    @GetMapping("/info")
    public String getInfo(HttpServletRequest request) {
        String username = request.getUserPrincipal().getName();
        String ssn = "123-45-6789"; // Dummy SSN for demonstration purposes

        return "Username: " + username + "<br>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4);
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


Or in your `build.gradle` if you are using Gradle:




tasks.named('bootJar') {
    enabled = true
}