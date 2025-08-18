import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

@SpringBootApplication
@RestController
public class ImageServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(ImageServerApplication.class, args);
    }

    @GetMapping("/img")
    public byte[] img(@RequestParam("file") String fileName) throws IOException {
        File file = new File(fileName);

        if (!file.exists()) {
            throw new IllegalArgumentException("File not found: " + fileName);
        }

        try (InputStream inputStream = new FileInputStream(file)) {
            return inputStream.readAllBytes();
        }
    }
}