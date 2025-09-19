import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return "Redirecting to example.com...";
        } else {
            return "Error: Invalid URL domain.";
        }
    }
}


To run this code, you will need a Java environment with Spring Boot dependencies. You can add the following dependency to your `pom.xml` if using Maven:


<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>


Or, use Gradle by adding this to your `build.gradle`:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}