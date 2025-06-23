package com.codewars;
    import org.springframework.boot.*;
    import org.springframework.boot.autoconfigure.*;
    import org.springframework.web.bind.annotation.*;
    
    @RestController
    @EnableAutoConfiguration
    public class Codewars {
        @RequestMapping("/check")
        String check(@RequestBody String payload) {
            return payload;
        }
        public static void main(String[] args) throws Exception {
            SpringApplication.run(Codewars.class, args);
        }
    }