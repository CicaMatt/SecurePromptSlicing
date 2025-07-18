import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.*;
@RestController
public class WebApp {
    @GetMapping("/api")
    public String getAPI(@RequestParam(name = "payload") String payload) {
        return loadPayloadIntoDictionary(payload);
    }
}