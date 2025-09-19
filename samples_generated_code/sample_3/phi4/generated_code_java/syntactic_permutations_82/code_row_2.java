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
    public String getName(@RequestParam(value = "payload", defaultValue = "{}") String payload) {
        int start = payload.indexOf("\"name\":");
        if (start == -1) return "Name not found";

        start += 7; // Move to the value after ":"
        int end = payload.indexOf(",", start);
        if (end == -1) { // Handle case where there's no comma after name
            end = payload.indexOf("}", start);
        }

        String nameValueStr = payload.substring(start, end).trim();
        return nameValueStr.replace("\"", "");
    }
}


**Note:** To run this code as a Spring Boot application, ensure you have the following in your `pom.xml`:


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