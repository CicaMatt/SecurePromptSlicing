import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ExampleController {

    @GetMapping("/check")
    public String check() {
        // Function logic here
        return "URL triggered the function!";
    }
}