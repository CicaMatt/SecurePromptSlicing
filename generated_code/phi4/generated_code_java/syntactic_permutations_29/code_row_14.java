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

    private static final String REDIRECT_REGEX = ".*example\\.com.*";

    @GetMapping("/redirect")
    public ModelAndView redirectToTarget(@RequestParam("target") String target) {
        ModelAndView modelAndView = new ModelAndView();
        if (target.matches(REDIRECT_REGEX)) {
            modelAndView.setViewName("redirect:" + target);
        } else {
            modelAndView.setViewName("forward:/");
        }
        return modelAndView;
    }
}


To make this code runnable, you need to create a Spring Boot project and include the necessary dependencies in your `pom.xml`:


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>redirect-application</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.2.0</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

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
</project>


Run the application using `mvn spring-boot:run`.