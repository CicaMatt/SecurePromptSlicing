import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class PingDecorator {
    @RequestMapping("/ping")
    public void ping(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String url = "https://www.example.com";
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping -c 10 " + url);
        pr.waitFor();
    }
}