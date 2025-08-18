import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.session.data.redis.config.annotation.web.http.EnableRedisHttpSession;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpSession;

@SpringBootApplication
@EnableRedisHttpSession
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @RestController
    static class InfoController {

        @GetMapping("/info")
        public String info(HttpSession session) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLastFour = (String) session.getAttribute("ssnLastFour");

            return "Username: " + username + "<br>" +
                   "Email: " + email + "<br>" +
                   "SSN Last 4: " + ssnLastFour;
        }
    }
}