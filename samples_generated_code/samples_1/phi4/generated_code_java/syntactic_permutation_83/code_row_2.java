import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class NameController {

    @GetMapping("/get-name")
    public String getName(@RequestParam(required = false) String name) {
        if (name != null && !name.isEmpty()) {
            return "Name: " + name;
        } else {
            return "No name provided";
        }
    }
}
