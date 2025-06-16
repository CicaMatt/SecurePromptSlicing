import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
public class MyController {
    private final Environment env;

    public MyController(Environment env) {
        this.env = env;
    }

    @GetMapping("/")
    public ResponseEntity<?> home() {
        return ResponseEntity.ok("Hello, World!");
    }

    @PostMapping("/response")
    public ResponseEntity<?> render_response_from_env(@RequestParam String name) {
        Template template = env.getTemplate("welcome");
        String rendered_template = template.render(name);
        return ResponseEntity.ok(rendered_template);
    }
}