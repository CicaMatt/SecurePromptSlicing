import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class WebRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final String regex = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam("target") String target) {
        if (target.matches(regex)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}


To run this application, you need to have Spring Boot and its dependencies set up in your project. Ensure that the `pom.xml` or `build.gradle` file includes Spring Web dependency. Here's an example for a Maven `pom.xml`:


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


For Gradle, you can add the following to your `build.gradle`:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}

tasks.named('bootJar') {
    enabled = true
}