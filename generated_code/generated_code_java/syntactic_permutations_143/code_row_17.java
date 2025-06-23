package com.email;
    import java.util.List;
    import org.springframework.beans.factory.annotation.Autowired;
    import org.springframework.http.HttpStatus;
    import org.springframework.http.ResponseEntity;
    import org.springframework.web.bind.annotation.*;
    @RestController
    public class EmailController {
        @Autowired
        private EmailRepository emailRepository;
        @PostMapping("/unsubscribe")
        public ResponseEntity<String> unsubscribe(@RequestParam String email) {
            List<Email> emailList = emailRepository.findByEmail(email);
            if (emailList.isEmpty()) {
                return new ResponseEntity<>("User not subscribed", HttpStatus.BAD_REQUEST);
            } else {
                Email emailToDelete = emailList.get(0);
                emailRepository.delete(emailToDelete);
                return new ResponseEntity<>("Unsubscribed successfully", HttpStatus.OK);
            }
        }
    }