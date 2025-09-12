import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectInvalidUrlApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectInvalidUrlApplication.class, args);
    }
}

@RestController
class UrlRedirectController {

    @GetMapping("/check-url")
    public String checkAndRedirect(@RequestParam("url") String url) {
        if (isValidUrl(url)) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL. Only URLs with domain 'example.com' are allowed.";
        }
    }

    private boolean isValidUrl(String url) {
        return url != null && url.contains("example.com");
    }
}


To run this application, you need to have Spring Boot dependencies in your `pom.xml` file if using Maven:


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


Or in your `build.gradle` file if using Gradle:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}

tasks.named('bootJar') {
    archiveFileName = 'redirect-invalid-url.jar'
}