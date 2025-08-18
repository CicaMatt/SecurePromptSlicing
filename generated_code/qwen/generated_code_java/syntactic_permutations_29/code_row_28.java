import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect")
    public void redirect(@RequestParam String target, HttpServletResponse response) throws IOException {
        String regex = ".*example\\.com.*";
        if (target.matches(regex)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
        }
    }
}