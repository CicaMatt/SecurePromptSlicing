import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public ResponseEntity<String> redirect_invalid_url(@RequestParam String url) {
        if (url.contains("example.com")) {
            return ResponseEntity.status(302).header("Location", url).build();
        } else {
            return ResponseEntity.badRequest().body("Error: Invalid URL");
        }
    }
}