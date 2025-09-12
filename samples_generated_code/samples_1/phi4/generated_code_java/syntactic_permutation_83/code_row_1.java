import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class PayloadController {

    @PostMapping("/checkName")
    public String checkName(@RequestBody Map<String, Object> payload) {
        if (payload.containsKey("name")) {
            return (String) payload.get("name");
        } else {
            return "Field 'name' does not exist.";
        }
    }
}


To run this code:

1. Ensure you have Maven and JDK installed.
2. Create a new Spring Boot project, or add the above classes to an existing one.
3. Add the following dependencies in your `pom.xml` if they are not already present:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


4. Run the application using `mvn spring-boot:run`.