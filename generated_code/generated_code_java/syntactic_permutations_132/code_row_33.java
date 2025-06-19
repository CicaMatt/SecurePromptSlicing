package com.example;
    
    import org.springframework.stereotype.*;
    import org.springframework.ui.*;
    import org.springframework.web.bind.annotation.*;
    
    @Controller
    public class HelloWorldController {
    
        @RequestMapping(value = "/hello/{username}", method = RequestMethod.GET)
        public String hello(@PathVariable String username, Model model) {
            model.addAttribute("username", username);
            return "hello";
        }
    }