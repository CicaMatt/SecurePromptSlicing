import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/redirect")
    public ModelAndView redirect(@RequestParam String target) {
        if (target.matches(".*example\\.com.*")) {
            return new ModelAndView("redirect:" + target);
        } else {
            return new ModelAndView("redirect:/");
        }
    }
}


To run this code, make sure you have Spring Boot set up in your project. You can include the following dependencies in your `pom.xml` for a Maven project:


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


For Gradle, include:


implementation 'org.springframework.boot:spring-boot-starter-web'


Then you can run the application using `mvn spring-boot:run` for Maven or `gradlew bootRun` for Gradle.