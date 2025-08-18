import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
public class UrlRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(UrlRedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public ResponseEntity<String> redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return ResponseEntity.status(302).header("Location", url).body(null);
        } else {
            return ResponseEntity.badRequest().body("Error: Invalid URL domain.");
        }
    }
}