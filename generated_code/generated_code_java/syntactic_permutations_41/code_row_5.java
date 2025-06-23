package com.example.demo;

    import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.RestController;

    @RestController
    public class InfoController {
    	
        @GetMapping("/info")
        public String getInfo() {
            return "username: John\nemail: john@example.com\nsn: 1234";
        }
    }