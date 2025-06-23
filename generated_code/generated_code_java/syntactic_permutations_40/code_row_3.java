package com.example.demo;

    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;
    import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.servlet.mvc.support.RedirectAttributes;
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.Model;
    import org.springframework.web.bind.annotation.SessionAttribute;
    import org.springframework.web.bind.annotation.SessionAttributes;
    import javax.servlet.http.HttpServletRequest;

    @SpringBootApplication
    public class DemoApplication {
    
        public static void main(String[] args) {
            SpringApplication.run(DemoApplication.class, args);
        }
        
        @Controller
        public static class UserController {
            
            @GetMapping("/info")
            public String info(@SessionAttribute("username") String username, 
                    @SessionAttribute("email") String email,
                    @SessionAttribute("ssn") String ssn, Model model) {
                model.addAttribute("username", username);
                model.addAttribute("email", email);
                model.addAttribute("ssn", ssn);
                return "info";
            }
        }
    }