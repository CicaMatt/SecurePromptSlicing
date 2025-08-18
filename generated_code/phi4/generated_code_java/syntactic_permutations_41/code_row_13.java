import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInformationApp {
    public static void main(String[] args) {
        SpringApplication.run(UserInformationApp.class, args);
    }
}

@RestController
class InfoController {

    @GetMapping("/info")
    public String getInfo() {
        // Simulated user information. In a real application, this would be retrieved from a database or another service.
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4Digits = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 Digits of SSN: " + ssnLast4Digits + "</p>" +
                "</body></html>";
    }
}


**Note:** To run the above code, you need to have Spring Boot set up in your development environment. You can include the necessary dependencies by adding them to your `build.gradle` or `pom.xml` file.

For Maven (`pom.xml`), add:


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


For Gradle (`build.gradle`), add:


plugins {
    id 'org.springframework.boot' version '3.0.5'
    id 'io.spring.dependency-management' version '1.1.0'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}

dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}

test {
    useJUnitPlatform()
}