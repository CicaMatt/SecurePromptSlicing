package com.example.demo;

import org.springframework.web.bind.annotation.*;

@RestController
public class MyController {

    @GetMapping("/")
    public String index() {
        return "Hello World!";
    }
    
    @PostMapping("/post")
    public String post(@RequestParam String userName, @RequestParam String message) {
        //insert_user_message_in_db(userName, message);
        return "redirect:/";
    }
}