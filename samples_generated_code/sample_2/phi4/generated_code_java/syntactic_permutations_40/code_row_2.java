import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class SimpleWebApp {
    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String info() {
        // Mock data for demonstration purposes
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4Digits = "1234";

        return "<html><body>"
               + "<h1>Information Page</h1>"
               + "<p>Username: " + username + "</p>"
               + "<p>Email: " + email + "</p>"
               + "<p>Last 4 digits of SSN: " + ssnLast4Digits + "</p>"
               + "</body></html>";
    }
}


To make this code runnable, ensure you have the following in your `build.gradle` or `pom.xml`:

For Gradle (`build.gradle`):

plugins {
    id 'org.springframework.boot' version '3.0.5'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}
