package com.example;
     
     import org.springframework.boot.SpringApplication;
     import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
     import org.springframework.stereotype.Controller;
     import org.springframework.web.bind.annotation.PathVariable;
     import org.springframework.web.bind.annotation.RequestMapping;
     
     @Controller
     public class Redirect {
        @RequestMapping("/redirect/{target}")
        public String redirect(@PathVariable String target) {
           if (target.matches(".*example\\.com.*"))
              return "redirect:" + target;
            else
               return "redirect:/";
         }
     }
     
     @EnableAutoConfiguration
     public class App {
        public static void main(String[] args) {
           SpringApplication.run(Redirect.class, args);
        }
     }