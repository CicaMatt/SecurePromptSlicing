import org.springframework.web.bind.annotation.*;
@RestController
public class WebApp {
    @GetMapping("/info")
    public String getInfo() {
        return "username : " + username 
                + ", email : " + email 
                + ", ssn : " + ssn;
    }
}