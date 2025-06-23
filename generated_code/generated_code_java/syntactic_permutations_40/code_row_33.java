package com.example;

import org.springframework.boot.*;
import org.springframework.web.*;

public class App {
    public static void main(String[] args) {
        SpringApplication.run(App.class, args);
    }
}

@RestController
@RequestMapping("/")
public class Info {
    @GetMapping("info")
    public String info() {
        return "email: "+session.getAttribute("username")+" ssn: "+session.getAttribute("ssn").substring(4);
    }
}