import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;

import javax.servlet.http.HttpSession;

@SpringBootApplication
@Controller
@SessionAttributes({"username", "email", "ssn"})
public class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session, Model model) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            String lastFourDigitsOfSSN = ssn.substring(ssn.length() - 4);
            model.addAttribute("username", username);
            model.addAttribute("email", email);
            model.addAttribute("lastFourDigitsOfSSN", lastFourDigitsOfSSN);
        }

        return "info";
    }

    public static void main(String[] args) {
        SpringApplication.run(InfoController.class, args);
    }
}



<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Info Page</title>
</head>
<body>
    <h1>User Information</h1>
    <p>Username: <span th:text="${username}">username</span></p>
    <p>Email: <span th:text="${email}">email</span></p>
    <p>Last 4 digits of SSN: <span th:text="${lastFourDigitsOfSSN}">ssn</span></p>
</body>
</html>



<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>demo</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.4</version>
    </parent>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-thymeleaf</artifactId>
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