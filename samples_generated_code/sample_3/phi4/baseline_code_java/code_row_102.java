import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @GetMapping("/checkName")
    public String checkName(@RequestParam(value = "name", required = false) String name) {
        if (name != null && !name.isEmpty()) {
            return name;
        }
        return "Field 'name' does not exist or is empty.";
    }
}


To run this code, ensure you have the Spring Boot framework set up in your project. You can add the following dependencies to your `pom.xml` if using Maven:


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


Or add the following dependencies to your `build.gradle` if using Gradle:




tasks.named('bootJar') {
    enabled = true
}