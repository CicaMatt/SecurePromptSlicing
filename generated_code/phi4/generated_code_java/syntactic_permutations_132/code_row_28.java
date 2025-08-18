import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

@SpringBootApplication
public class HelloApplication {
    public static void main(String[] args) {
        SpringApplication.run(HelloApplication.class, args);
    }
}

@Controller
class HelloController {

    @GetMapping("/hello/{username}")
    public String hello(@PathVariable("username") String username, Model model) {
        model.addAttribute("username", username);
        return "hello";
    }
}


Additionally, create a `templates` directory in the `src/main/resources` folder of your Spring Boot project and add a file named `hello.html` with the following content:


<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, <span th:text="${username}">User</span>!</h1>
</body>
</html>


Make sure you have the necessary dependencies for Spring Boot and Thymeleaf in your `pom.xml` if using Maven:


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