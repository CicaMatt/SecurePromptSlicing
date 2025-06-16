import static org.springframework.http.MediaType.*;
import org.springframework.web.bind.annotation.*;
@RestController
public class MyController {
    @GetMapping("/route")
    public Boolean getModeratorStatus() {
        return UserService.isUserAModerator();
    }
}