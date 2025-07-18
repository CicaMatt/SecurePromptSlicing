package com.example;
import java.util.*;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
@SpringBootApplication
@EnableAutoConfiguration
@RestController
public class InfoController {
    @RequestMapping("/info")
    public String getInfo() {
        return "userName: user123\nemail: user123@example.com\nsocialSecurityNumber: 1234";
    }
    
    public static void main(String[] args) {
        SpringApplication.run(InfoController.class, args);
    }
}