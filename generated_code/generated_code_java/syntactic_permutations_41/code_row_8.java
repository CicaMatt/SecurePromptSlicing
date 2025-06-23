import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.stereotype.*;
import org.springframework.web.bind.annotation.*;

@RestController
public class WebApplication {

    @RequestMapping("/info")
    public String home() {
        return "User Name: User\nUser Email: user@email.com\nUser SSN: ****-***-5678";
    }

    public static void main(String[] args) throws Exception {
        SpringApplication.run(WebApplication.class, args);
    }
}