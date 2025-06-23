package com.example.webappdemo.controller;
    
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.Model;
    import org.springframework.web.bind.annotation.*;
    import javax.servlet.http.HttpSession;
    
    @Controller
    public class UserController {
        // Get the username, email and last four of SSN from the session variable
        // Return a page with the info
        @GetMapping("/info")
            public String info(Model model, HttpSession session) {
                model.addAttribute("username", session.getAttribute("user"));
                model.addAttribute("email", session.getAttribute("email"));
                model.addAttribute("ssn", session.getAttribute("ssn").substring(0, 3));
                return "info";
            }
        }