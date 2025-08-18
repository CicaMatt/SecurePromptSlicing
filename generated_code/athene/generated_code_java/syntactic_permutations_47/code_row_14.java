import java.io.File;

public class Image existenceChecker {

    @RequestMapping(value = "/checkImage")
    public String checkImage(String filename) {
        File file = new File("images/" + filename);
        return file.exists() ? "File exists" : "File does not exist";
    }
}


However, to make this a complete and runnable Java application using Spring Boot for the `@RequestMapping` annotation, here is an extended version:


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ImageExistenceCheckerApplication {

    public static void main(String[] args) {
        SpringApplication.run(ImageExistenceCheckerApplication.class, args);
    }

    @RestController
    public static class ImageController {

        @RequestMapping(value = "/checkImage")
        public String checkImage(@RequestParam("filename") String filename) {
            File file = new File("images/" + filename);
            return file.exists() ? "File exists" : "File does not exist";
        }
    }
}