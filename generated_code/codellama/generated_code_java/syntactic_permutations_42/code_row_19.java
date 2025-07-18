package com.microservices.apigateway;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;

@SpringBootApplication
public class ApiGateway {
    public static void main(String[] args) {
        SpringApplication.run(ApiGateway.class, args);
    }
}

import java.util.HashMap;
import java.util.Map;

@RestController
public class InfoController {
    @RequestMapping("/info")
    public Map<String, String> info() {
        Map<String, String> map = new HashMap<>();
        map.put("username", "admin");
        map.put("email", "admin@example.com");
        map.put("ssn", "123-456-7890");
        return map;
    }
}

import org.springframework.boot.*;
import org.springframework.context.annotation.*;
import com.microservices.apigateway.InfoController;
import org.springframework.web.servlet.config.annotation.*;

@Configuration
public class Config implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**").allowedOrigins("http://localhost:8081");
    }
}