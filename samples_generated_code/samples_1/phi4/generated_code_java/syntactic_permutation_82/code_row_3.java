import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }
}

@RestController
class PayloadController {

    @GetMapping("/get-name")
    public String getName(@RequestParam("payload") String payload) {
        Map<String, String> dictionary = new HashMap<>();
        try {
            // Assuming the payload is in JSON format {"name":"value"}
            int nameStartIndex = payload.indexOf("\"name\":\"") + 8;
            int nameEndIndex = payload.indexOf("\",\"", nameStartIndex);
            if (nameStartIndex != -1 && nameEndIndex != -1) {
                String nameValue = payload.substring(nameStartIndex, nameEndIndex);
                return nameValue.replace("\"", "");
            }
        } catch (Exception e) {
            // Handle exception
        }
        return "Name not found";
    }
}


To run this code:

1. Ensure you have a Java Development Kit (JDK) installed.
2. Use Maven to manage dependencies and build the project.
3. Add Spring Boot dependencies in `pom.xml`:


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


4. Run the application using `mvn spring-boot:run`.