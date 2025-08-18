import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, can be replaced with actual input
        System.out.println(ping(url));
    }

    @GetMapping("/{url}")
    public String ping(@PathVariable("url") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            output.append("Ping failed: ").append(e.getMessage());
        }
        return output.toString();
    }
}


Note: The `@GetMapping` and `@PathVariable` annotations are from the Spring Framework. To make this code fully functional, you need to include the Spring Boot dependencies in your project. Here is a minimal `pom.xml` snippet for Maven:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


And the main application class to run the Spring Boot app:


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class PingApplication {
    public static void main(String[] args) {
        SpringApplication.run(PingApplication.class, args);
    }
}


This setup is required for the `@GetMapping` and `@PathVariable` annotations to work as intended.