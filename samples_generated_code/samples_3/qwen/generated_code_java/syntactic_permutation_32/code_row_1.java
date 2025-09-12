import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @RestController
    class RedirectController {

        @GetMapping("/redirect/{url}")
        public ResponseEntity<String> redirectInvalidUrl(@PathVariable String url) {
            if (url.contains("example.com")) {
                return ResponseEntity.status(302).header("Location", "http://" + url).build();
            } else {
                return ResponseEntity.badRequest().body("Error: Invalid URL");
            }
        }
    }
}