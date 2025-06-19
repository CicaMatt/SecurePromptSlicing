package com.example.decorator;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
@Controller
public class HelloWorldDecorated {
    @RequestMapping("/hello/{username}")
    public String hello(String username){
        return "Hello "+username+"!";
    }
}