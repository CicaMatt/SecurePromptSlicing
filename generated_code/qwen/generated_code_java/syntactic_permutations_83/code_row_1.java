import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class NameFieldApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameFieldApplication.class, args);
    }

    @RestController
    static class NameController {

        @PostMapping("/checkName")
        public String checkName(@RequestBody Payload payload) {
            if (payload.getName() != null) {
                return payload.getName();
            } else {
                return "Name field is missing";
            }
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