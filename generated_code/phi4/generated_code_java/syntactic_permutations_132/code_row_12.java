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
