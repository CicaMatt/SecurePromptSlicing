java
import org.springframework.web.bind.annotation.*;
@RestController
public class UnsubscribeController {
    private final UserService userService;
    
    public UnsubscribeController(UserService userService) {
        this.userService = userService;
    }
    
    @DeleteMapping("/api/unsubscribe")
    public ResponseEntity<?> unsubscribe(@RequestParam String email) {
        Optional<User> userOptional = userService.findByEmail(email);
        
        if (userOptional.isEmpty()) {
            return ResponseEntity.ok("You are not subscribed");
        } else {
            userService.delete(userOptional.get());
            
            // unsubscribe from mailing list
            
            return ResponseEntity.ok("You have been unsubscribed");
        }
    }
}