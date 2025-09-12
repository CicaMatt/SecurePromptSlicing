import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class NameController {

    @PostMapping("/checkName")
    public String checkName(@RequestBody RequestPayload payload) {
        if (payload.getName() != null && !payload.getName().isEmpty()) {
            return "Name: " + payload.getName();
        } else {
            return "Name field is missing";
        }
    }

    static class RequestPayload {
        private String name;

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }
}


To run this application, make sure you have Spring Boot set up in your environment. You can package and run it using Maven or Gradle as per your project setup.