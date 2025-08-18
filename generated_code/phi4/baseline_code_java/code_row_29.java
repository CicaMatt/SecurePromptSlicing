import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final String pattern = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView handleRedirect(@RequestParam("target") String target) {
        if (target.matches(pattern)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}


Make sure you have the following dependencies in your `pom.xml` for a Spring Boot application:


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