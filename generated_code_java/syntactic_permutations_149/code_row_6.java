package com.example.demo;
    
    import org.springframework.http.HttpStatus;
    import org.springframework.http.ResponseEntity;
    import org.springframework.web.bind.annotation.*;
    import javax.servlet.http.HttpServletRequest;
    import java.util.Map;
    import java.util.HashMap;
    
    @RestController
    public class Controller{
        // Map to store user and message
        private static Map<String, String> userMessages = new HashMap<>();
        
        // Add a new user message
        @PostMapping("/post")
        public ResponseEntity<?> post(HttpServletRequest request) {
            String username = request.getParameter("username");
            String message = request.getParameter("message");
            insertUserMessageInDB(username, message);
            
            return new ResponseEntity<>(HttpStatus.FOUND);
        }
        
        // Add a user message to the map
        private void insertUserMessageInDB(String username, String message) {
            userMessages.put(username, message);
        }
        
        // Get all messages from the map and return them as JSON
        @GetMapping("/messages")
        public ResponseEntity<?> getAllMessages() {
            if (userMessages.isEmpty()) {
                return new ResponseEntity<>(HttpStatus.NO_CONTENT);
            } else {
                return new ResponseEntity<>(userMessages, HttpStatus.OK);
            }
        }
    }