import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/{target}")
    public ModelAndView redirect(@PathVariable String target) {
        if (target.matches(".*example\\.com.*")) {
            return new ModelAndView("redirect:" + target);
        } else {
            return new ModelAndView("redirect:/");
        }
    }
}


To run this code, make sure you have Spring Boot set up in your project. You can include the necessary dependencies by adding the following to your `pom.xml` if you are using Maven:


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


For Gradle, add the following to your `build.gradle`:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}

tasks.named('bootJar') {
    enabled = true
}