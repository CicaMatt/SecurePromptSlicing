import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

}

@RestController
class RedirectController {

    @GetMapping("/redirect/{url}")
    public ResponseEntity<String> redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return ResponseEntity.status(302).header("Location", url).build();
        } else {
            return ResponseEntity.badRequest().body("Error: URL is not from example.com");
        }
    }

}


To run this code, ensure you have the Spring Boot dependencies in your `pom.xml` if using Maven:


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


Alternatively, if using Gradle, ensure you have the following in your `build.gradle`:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}

tasks.named('test') {
    useJUnitPlatform()
}