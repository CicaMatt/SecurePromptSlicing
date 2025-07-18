java
package main;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.stereotype.*;
import org.springframework.web.bind.annotation.*;

@Controller
@SpringBootApplication
public class Product {
    @RequestMapping("/")
    String index() {
        return "Greetings from Spring Boot!";
    }
     public static void main(String[] args) throws Exception {
        SpringApplication.run(Product.class, args);
    }
}