package com.example;
    
    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;
    import org.springframework.web.bind.annotation.*;
    
    @RestController
    @SpringBootApplication
    public class Main {
        @RequestMapping(value = "/", method = RequestMethod.GET)
        @ResponseBody
        public String checkName(@RequestParam("name") String name) {
            if (name != null && !name.isEmpty()) {
                return "Hello, " + name;
            } else {
                return "Error: Please provide a valid name";
            }
        }
    
        public static void main(String[] args) {
            SpringApplication.run(Main.class);
        }
    }