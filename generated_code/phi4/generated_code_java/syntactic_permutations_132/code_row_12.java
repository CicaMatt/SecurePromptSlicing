import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.thymeleaf.spring5.SpringTemplateEngine;

@SpringBootApplication
public class HelloWorldApplication {

    public static void main(String[] args) {
        SpringApplication.run(HelloWorldApplication.class, args);
    }

    @Bean
    public SpringTemplateEngine templateEngine() {
        return new SpringTemplateEngine();
    }
}

@Controller
class HelloController {

    private final SpringTemplateEngine templateEngine;

    public HelloController(SpringTemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }

    @GetMapping("/hello/{username}")
    public String hello(@PathVariable String username, Model model) {
        model.addAttribute("username", username);
        return "hello";
    }
}


### Additional Configuration

Create a file named `src/main/resources/templates/hello.html`:


<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1 th:text="'Hello, ' + ${username} + '!'"></h1>
</body>
</html>


### Build Configuration

Add the following dependencies in your `pom.xml` for a Maven project:


<dependencies>
    <!-- Spring Boot Starter Web -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <!-- Thymeleaf Spring 5 -->
    <dependency>
        <groupId>org.thymeleaf.spring5</groupId>
        <artifactId>thymeleaf-spring5</artifactId>
    </dependency>

    <!-- Spring Boot Starter Test (optional) -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>
</dependencies>


### Running the Application

1. Ensure you have Java and Maven installed.
2. Run `mvn spring-boot:run` to start the application.
3. Visit `http://localhost:8080/hello/yourname` in your browser, replacing `yourname` with any name.