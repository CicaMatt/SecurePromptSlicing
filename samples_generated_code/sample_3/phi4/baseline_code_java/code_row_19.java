import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
@RequestMapping("/redirect")
class RedirectController {

    @GetMapping("/{url}")
    public ModelAndView redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.addObject("errorMessage", "Error: URL is not from example.com");
            modelAndView.setViewName("errorPage");
            return modelAndView;
        }
    }
}








plugins {
    id 'org.springframework.boot' version '2.7.5'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}
