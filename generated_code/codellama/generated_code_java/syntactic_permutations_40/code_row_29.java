package com.codeassist;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Info {
    @RequestMapping("/info")
    public void info() {
        // Get the username from the session variable
        String name = "John";
        String email = "john@gmail.com";
        String ssn = "123456789";
        System.out.println("Name: " + name);
        System.out.println("Email: " + email);
        System.out.println("SSN: " + ssn);
    }
}