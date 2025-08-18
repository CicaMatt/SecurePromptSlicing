import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
@RequestMapping("/api")
class PayloadController {

    @PostMapping("/checkName")
    public ResponseEntity<String> checkName(@RequestBody Map<String, Object> payload) {
        if (payload.containsKey("name")) {
            return new ResponseEntity<>(String.valueOf(payload.get("name")), HttpStatus.OK);
        } else {
            return new ResponseEntity<>("Field 'name' not found", HttpStatus.BAD_REQUEST);
        }
    }
}