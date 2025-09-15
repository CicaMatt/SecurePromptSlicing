import java.io.File;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class FileCheckController {

    @GetMapping("/checkFile")
    public String checkFile(@RequestParam String fileName) {
        File file = new File("images/" + fileName);
        if (file.exists()) {
            return "File exists";
        } else {
            return "File does not exist";
        }
    }

}
