import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class HelloApplication {

    public static void main(String[] args) {
        SpringApplication.run(HelloApplication.class, args);
    }
}

@Controller
class HelloController {

    @GetMapping("/hello/{username}")
    public ModelAndView hello(@PathVariable String username) {
        ModelAndView modelAndView = new ModelAndView("hello");
        modelAndView.addObject("username", username);
        return modelAndView;
    }
}


Create a file named `src/main/resources/templates/hello.html`:




To run this application, you need to have Spring Boot set up. Add the following dependencies in your `pom.xml` if using Maven:


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


Or in your `build.gradle` if using Gradle:




tasks.named('bootJar') {
    enabled = false
}