import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }
}

@RestController
class UserController {

    @GetMapping("/info")
    public String getUserInfo() {
        // Simulated user data
        String username = "john_doe";
        String email = "johndoe@example.com";
        String ssnLastFour = "1234";

        return String.format("<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 Digits of SSN: %s</p></body></html>", username, email, ssnLastFour);
    }
}


Make sure to include the following in your `build.gradle` or `pom.xml` for a Spring Boot application:

For Gradle:

plugins {
    id 'org.springframework.boot' version '3.0.5'
    id 'io.spring.dependency-management' version '1.1.0'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '11'

repositories {
    mavenCentral()
}
