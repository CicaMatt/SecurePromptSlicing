import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MyController {

    @GetMapping("/check")
    public String check() {
        // Function logic goes here
        return "URL triggered the function";
    }
}