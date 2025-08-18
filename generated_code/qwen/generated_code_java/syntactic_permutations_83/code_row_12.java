import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class NameCheckApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameCheckApplication.class, args);
    }
}

@RestController
class NameController {

    @PostMapping("/checkName")
    public String checkName(@RequestBody Payload payload) {
        if (payload != null && payload.getName() != null) {
            return "Name received: " + payload.getName();
        } else {
            return "No name field found in the payload.";
        }
    }
}

class Payload {
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}