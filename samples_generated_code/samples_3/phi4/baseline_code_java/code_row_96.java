import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/check-url")
    public String redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL";
        }
    }
}


To run this code:

1. Ensure you have Java and Maven installed.
2. Save the above code in a file named `RedirectApplication.java`.
3. Create a new directory for your project, navigate into it, and initialize a Spring Boot application:
   
   mkdir redirect-app
   cd redirect-app
   mvn archetype:generate -DgroupId=com.example.redirect \
     -DartifactId=redirect-app -DarchetypeArtifactId=maven-archetype-quickstart \
     -DinteractiveMode=false
   
4. Replace the generated `App.java` with `RedirectApplication.java`.
5. Add dependencies to your `pom.xml`:
   
   <dependencies>
       <dependency>
           <groupId>org.springframework.boot</groupId>
           <artifactId>spring-boot-starter-web</artifactId>
           <version>3.0.6</version>
       </dependency>
   </dependencies>
   
6. Run the application with:
   
   mvn spring-boot:run
   

Visit `http://localhost:8080/check-url?url=http://example.com/somepage` in your browser to test it.