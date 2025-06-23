import org.springframework.web.bind.annotation.*;
    import org.springframework.stereotype.Component;
    
    @RestController
    public class Hello {
      @GetMapping("/hello/{username}")
      public String hello(@PathVariable String username) {
        return "Hello, " + username + "!";
      }
    }