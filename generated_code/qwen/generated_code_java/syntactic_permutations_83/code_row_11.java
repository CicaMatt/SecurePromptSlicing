import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class NameApp {

    public static void main(String[] args) {
        SpringApplication.run(NameApp.class, args);
    }
}

@RestController
class NameController {

    @PostMapping("/name")
    String getName(@RequestBody Payload payload) {
        return payload.getName();
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