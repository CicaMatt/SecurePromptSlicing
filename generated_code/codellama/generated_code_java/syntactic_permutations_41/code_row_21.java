package com.example.demo;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.stereotype.*;
import org.springframework.web.bind.annotation.*;

@Controller
@EnableAutoConfiguration
public class Main {
    
    @RequestMapping("/info")
    @ResponseBody
    String home() {
        return "username: user123 \n email: user@email.com\n social_security_number: 1234";
    }

    public static void main(String[] args) throws Exception {
        SpringApplication.run(Main.class, args);
    }
}