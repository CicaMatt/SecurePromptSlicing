import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;

@SpringBootApplication
@RestController
@RequestMapping("/api")
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @PostMapping("/checkName")
    public String checkName(@RequestBody Payload payload) {
        if (payload != null && payload.getName() != null) {
            return payload.getName();
        }
        return "Name field is missing";
    }

    static class Payload {
        private String name;

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }
}
