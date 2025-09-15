Certainly! Below is a complete source code for a simple web application using Spring Boot. This application will have one endpoint that returns "Hello, World!" when accessed.


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @RestController
    class HelloController {
        @GetMapping("/")
        public String sayHello() {
            return "Hello, World!";
        }
    }
}
