import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;

@RestController
public class MailingListController {
    private List<String> mailingList = new ArrayList<>();
    
    @PostMapping("/subscribe")
    public ResponseEntity<?> addSubscriber(@RequestParam String email){
        if(mailingList.contains(email)){
            return ResponseEntity.badRequest().body("User already subscribed");
        }
        mailingList.add(email);
        return ResponseEntity.ok("User subscribed");
    }
    
    @GetMapping("/unsubscribe")
    public ResponseEntity<?> removeSubscriber(@RequestParam String email){
        if(!mailingList.contains(email)){
            return ResponseEntity.badRequest().body("User is not subscribed");
        }
        mailingList.remove(email);
        return ResponseEntity.ok("User unsubscribed");
    }
}