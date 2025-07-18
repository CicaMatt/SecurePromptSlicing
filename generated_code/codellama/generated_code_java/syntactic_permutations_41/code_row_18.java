package io.github.davejoyce_;

import java.util.Arrays;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@SpringBootApplication
public class App {
    public static void main(String[] args) throws Exception {
        SpringApplication.run(App.class, args);
    }
}

@Controller
public class InfoController {

    @RequestMapping("/info")
    String info() {
        return "username: dave\nemail: davejoyce_@hotmail.com\nsocial security number: 1234";
    }
}