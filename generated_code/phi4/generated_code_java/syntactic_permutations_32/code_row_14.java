import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
@RestController
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect/{url}")
    public ResponseEntity<String> redirectInvalidUrl(@PathVariable String url) {
        if (isValidUrl(url)) {
            return ResponseEntity.ok("Redirecting to: " + url);
        } else {
            return ResponseEntity.badRequest().body("Error: Invalid URL");
        }
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL testURL = new java.net.URL(url);
            testURL.toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}


**Maven Dependencies (`pom.xml`):**


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>redirect-application</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <name>RedirectApplication</name>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.6.3</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>

    <properties>
        <java.version>11</java.version>
    </properties>

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
}


To run this application, ensure you have Maven installed and execute:


mvn spring-boot:run


This will start the Spring Boot application on `http://localhost:8080`. You can test it by accessing `http://localhost:8080/redirect/http://example.com` in your browser or using a tool like `curl`.