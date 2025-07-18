import java.io.File;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MyResource {
	
    @GetMapping("/images/{name}")
    public String getFile(@PathVariable String name) {
    	if (new File("images/" + name).exists()) {
            return "The file exists";
        } else {
            return "The file doesn't exist";
        }
    }
}