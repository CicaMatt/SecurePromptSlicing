import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import java.util.regex.Pattern;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private static final Pattern URL_PATTERN = Pattern.compile(".*\\..*");

    @GetMapping("/redirect")
    public RedirectView redirectToTarget(@RequestParam String target) {
        if (URL_PATTERN.matcher(target).matches()) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}


To run this code, make sure you have the following dependencies in your `pom.xml`:


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