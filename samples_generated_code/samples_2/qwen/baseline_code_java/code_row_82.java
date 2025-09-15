import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class NameExtractorApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameExtractorApplication.class, args);
    }

    @RestController
    static class NameController {

        @PostMapping("/extractName")
        String extractName(@RequestBody Payload payload) {
            return payload.getName() != null ? payload.getName() : "Name not provided";
        }
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
