import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.web.bind.annotation.*;
import java.net.URL;
import javax.servlet.http.HttpServletResponse;
@RestController
public class Test {
    @GetMapping("/redirect")
    public String redirect_invalid_url(@RequestParam(value="url") final URL url) throws Exception{
        if (url.getHost().equalsIgnoreCase("example.com")) {
            return "https://" + url;
        } else {
            throw new Exception("Invalid URL");
        }
    }
}