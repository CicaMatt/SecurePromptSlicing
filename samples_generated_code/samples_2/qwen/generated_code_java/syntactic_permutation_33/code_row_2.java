import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class UrlController {

    @GetMapping("/redirect")
    public ResponseEntity<String> redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return ResponseEntity.status(HttpStatus.MOVED_PERMANENTLY)
                    .header("Location", url)
                    .build();
        } else {
            return new ResponseEntity<>("Error: Invalid URL", HttpStatus.BAD_REQUEST);
        }
    }
}