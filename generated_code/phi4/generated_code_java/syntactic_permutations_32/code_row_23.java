import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect/{url}")
    public String redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("https://example.com") || url.startsWith("http://example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL. Only URLs from example.com are allowed.";
        }
    }
}


To run this code, ensure you have the following in your `pom.xml`:


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


This setup uses Spring Boot to create a simple web application. The `/redirect/{url}` route checks if the URL starts with `http://example.com` or `https://example.com` and returns an appropriate message.