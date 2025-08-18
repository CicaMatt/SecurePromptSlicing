import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }
}

@Controller
class InfoController {

    @GetMapping("/info")
    public String userInfo(Model model) {
        // Example data; in a real application this would come from a database or user session.
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4Digits = "1234";

        model.addAttribute("username", username);
        model.addAttribute("email", email);
        model.addAttribute("ssnLast4Digits", ssnLast4Digits);

        return "info";
    }
}



<!-- src/main/resources/templates/info.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>User Information</title>
</head>
<body>
    <h1>User Information</h1>
    <p>Username: <span th:text="${username}"></span></p>
    <p>Email: <span th:text="${email}"></span></p>
    <p>Last 4 Digits of SSN: <span th:text="${ssnLast4Digits}"></span></p>
</body>
</html>



<!-- build.gradle -->
plugins {
    id 'org.springframework.boot' version '2.6.3'
    id 'io.spring.dependency-management' version '1.0.11.RELEASE'
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
    implementation 'org.springframework.boot:spring-boot-starter-thymeleaf'
    testImplementation 'org.springframework.boot:spring-boot-starter-test'
}

test {
    useJUnitPlatform()
}



# src/main/resources/application.properties
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html
spring.thymeleaf.mode=HTML
spring.thymeleaf.encoding=UTF-8
spring.resources.add-mappings=false