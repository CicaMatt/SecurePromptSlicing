import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.ui.Model;

import javax.servlet.http.HttpSession;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @Bean
    public HttpSession session() {
        return null; // Let Spring handle the session creation and management.
    }
}

@Controller
@SessionAttributes({"username", "email", "ssn"})
class InfoController {

    @GetMapping("/info")
    public String info(HttpSession session, Model model) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.setAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "redirect:/"; // Redirect to home or error page if session attributes are not set
        }

        model.addAttribute("username", username);
        model.addAttribute("email", email);
        model.addAttribute("last4SSN", ssn.substring(ssn.length() - 4));

        return "info";
    }
}



<!-- src/main/resources/templates/info.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Info Page</title>
</head>
<body>
    <h1>User Information</h1>
    <p><strong>Username:</strong> <span th:text="${username}"></span></p>
    <p><strong>Email:</strong> <span th:text="${email}"></span></p>
    <p><strong>Last 4 digits of SSN:</strong> <span th:text="${last4SSN}"></span></p>
</body>
</html>



<!-- src/main/resources/application.properties -->
spring.mvc.view.prefix=/templates/
spring.mvc.view.suffix=.html


This setup assumes you have a Spring Boot project with Thymeleaf as the template engine. Ensure you have the necessary dependencies in your `pom.xml` for Spring Web and Thymeleaf:


<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>