package main;
    import org.springframework.web.bind.annotation.*;
    @RestController
    public class WebApp {
        @GetMapping("/info")
        public String info(HttpSession session) {
            return "Welcome, " + session.getAttribute("username") + " (" + session.getAttribute("email") + ")";
        }
    }