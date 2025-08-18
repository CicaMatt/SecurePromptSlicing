import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/redirect/{url}")
    public ModelAndView redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.setViewName("error");
            modelAndView.addObject("message", "Error: Invalid URL. Only URLs from example.com are allowed.");
            return modelAndView;
        }
    }
}



<!-- src/main/resources/templates/error.html -->

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Error</title>
</head>
<body>
    <h1>Error Page</h1>
    <p th:text="${message}"></p>
</body>
</html>



# src/main/resources/application.properties

spring.mvc.view.prefix=/templates/
spring.mvc.view.suffix=.html