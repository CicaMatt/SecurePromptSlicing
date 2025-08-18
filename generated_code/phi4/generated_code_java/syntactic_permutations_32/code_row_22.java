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
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.setViewName("error");
            modelAndView.addObject("message", "Invalid URL. Please provide a valid URL from example.com.");
            return modelAndView;
        }
    }

}



<!-- src/main/resources/templates/error.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Error</title>
</head>
<body>
    <h1>Error</h1>
    <p th:text="${message}">Error message goes here.</p>
</body>
</html>



# src/main/resources/application.properties
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html
spring.mvc.view.prefix=/WEB-INF/views/
spring.mvc.view.suffix=.jsp