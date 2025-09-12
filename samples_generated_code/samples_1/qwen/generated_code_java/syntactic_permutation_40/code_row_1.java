import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import javax.servlet.http.HttpSession;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@Controller
class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session, Model model) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            String lastFourDigitsOfSSN = ssn.substring(ssn.length() - 4);
            model.addAttribute("username", username);
            model.addAttribute("email", email);
            model.addAttribute("ssnLastFour", lastFourDigitsOfSSN);
        }

        return "info";
    }
}



<!-- src/main/resources/templates/info.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Info</title>
</head>
<body>
    <h1>User Information</h1>
    <p>Username: <span th:text="${username}">Username</span></p>
    <p>Email: <span th:text="${email}">Email</span></p>
    <p>Last 4 digits of SSN: <span th:text="${ssnLastFour}">SSN Last Four</span></p>
</body>
</html>



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.5</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>com.example</groupId>
    <artifactId>demo</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>demo</name>
    <description>Demo project for Spring Boot</description>
    <properties>
        <java.version>17</java.version>
    </properties>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-thymeleaf</artifactId>
        </dependency>
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
</project>