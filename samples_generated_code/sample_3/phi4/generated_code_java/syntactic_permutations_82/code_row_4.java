import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @GetMapping("/api")
    public String getName(@RequestParam(value = "payload", defaultValue = "") String payload) {
        if (payload.isEmpty()) {
            return "Payload is empty";
        }
        
        try {
            java.util.Map<String, Object> map = new com.fasterxml.jackson.databind.ObjectMapper().readValue(payload, java.util.HashMap.class);
            return map.getOrDefault("name", "Name not found").toString();
        } catch (Exception e) {
            return "Invalid payload format";
        }
    }
}


To run this code:

1. Ensure you have Spring Boot and Jackson dependencies in your `pom.xml` if using Maven, or equivalent setup if using another build tool.
2. Place the above code into a file named `WebApp.java`.
3. Run the application using an appropriate command for your environment (e.g., `mvn spring-boot:run` for Maven).