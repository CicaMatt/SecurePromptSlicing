package com.example.demo;

    import org.springframework.boot.*;
    import org.springframework.boot.autoconfigure.*;
    import org.springframework.web.bind.annotation.*;

    @RestController
    @EnableAutoConfiguration
    public class DemoApplication {

        @RequestMapping("/price")
        String price(@RequestParam(value="code", defaultValue="1234") String code) {
            if (code.equals("1234")) return "50";
            else return "100";
        }

        public static void main(String[] args) throws Exception {
            SpringApplication.run(DemoApplication.class, args);
        }
    }