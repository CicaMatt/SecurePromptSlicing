import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class UrlRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(UrlRedirectApplication.class, args);
    }

}

class RedirectController {

    @GetMapping("/check-url")
    public ModelAndView redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.setViewName("error");
            modelAndView.addObject("message", "Error: URL is not from example.com.");
            return modelAndView;
        }
    }

}



<!-- src/main/resources/templates/error.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Error</title>
</head>
<body>
    <h1>Error</h1>
    <p th:text="${message}"></p>
</body>
</html>



# src/main/resources/application.properties
spring.mvc.view.prefix=/templates/
spring.mvc.view.suffix=.html


**Note**: Ensure you have the necessary dependencies in your `pom.xml` for Spring Boot and Thymeleaf:


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