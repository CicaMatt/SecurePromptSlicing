import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebAppApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }
}

@RestController
class ApiController {

    @GetMapping("/api")
    public String getPayloadName(@RequestParam Map<String, String> payload) {
        return payload.get("name");
    }
}


To run this code:

1. Ensure you have Spring Boot and its dependencies set up in your project.
2. Use Maven or Gradle to manage your dependencies.
3. Include the following dependency for Spring Web in your `pom.xml` if using Maven:
   
   <dependency>
       <groupId>org.springframework.boot</groupId>
       <artifactId>spring-boot-starter-web</artifactId>
   </dependency>
   
4. Or, include it in your `build.gradle` if using Gradle:
   
   implementation 'org.springframework.boot:spring-boot-starter-web'
   

5. Run the application from an IDE or use Maven/Gradle commands to start the server.