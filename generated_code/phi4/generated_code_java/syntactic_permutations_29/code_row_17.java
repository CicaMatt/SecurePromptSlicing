import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import java.util.regex.Pattern;

@SpringBootApplication
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }
}

@Controller
class RedirectController {

    private static final Pattern EXAMPLE_COM_PATTERN = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public ModelAndView redirect(@RequestParam String target) {
        if (EXAMPLE_COM_PATTERN.matcher(target).matches()) {
            return new ModelAndView("redirect:" + target);
        } else {
            return new ModelAndView("redirect:/");
        }
    }
}


To run this code, you need to have Spring Boot set up in your project. This includes having the necessary dependencies for Spring Web and Spring Boot Starter in your `pom.xml` or `build.gradle` file.