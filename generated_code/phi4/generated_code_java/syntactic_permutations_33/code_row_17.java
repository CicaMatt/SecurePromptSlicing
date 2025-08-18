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

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public ModelAndView redirectInvalidUrl(@RequestParam String url) {
        if (url.contains(".")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.addObject("errorMessage", "Invalid URL: Must contain a '.'");
            modelAndView.setViewName("error");
            return modelAndView;
        }
    }

}



<!-- error.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Error</title>
</head>
<body>
    <h1>Error</h1>
    <p th:text="${errorMessage}"></p>
</body>
</html>


**`application.properties`:**


spring.thymeleaf.prefix=classpath:/templates/