package com.example.demo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.stereotype.Controller;

@RestController
public class Controller {
    private Session session = new Session();
    
    @GetMapping("/info")
    public ModelAndView info() {
        String username = session.getUsername();
        String email = session.getEmail();
        String ssn = session.getSsn();
        
        ModelAndView mv = new ModelAndView("info");
        mv.addObject("username", username);
        mv.addObject("email", email);
        mv.addObject("ssn", ssn.substring(0, 3) + "***" + ssn.substring(6));
        
        return mv;
    }
}