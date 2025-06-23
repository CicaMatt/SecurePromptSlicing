import java.io.*;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;

@Controller
@EnableAutoConfiguration
public class Calculator {
    
    @GetMapping("/")
    public String getPrice(@RequestParam(value="quantity") int quantity, 
                        @RequestParam(value="price") double price) throws IOException{
        return String.format("Total Cost: %f", price*quantity);
    }

    public static void main(String[] args){
        SpringApplication.run(Calculator.class, args);
    }
}