import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.session.data.redis.config.annotation.web.http.EnableRedisHttpSession;
import org.springframework.web.context.annotation.SessionScope;
import org.springframework.beans.factory.annotation.Autowired;
import javax.servlet.http.HttpSession;

@SpringBootApplication
@EnableRedisHttpSession
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class InfoController {

    @Autowired
    private UserSession userSession;

    @GetMapping("/info")
    public String info() {
        return "Username: " + userSession.getUsername() + "<br>SSN Last 4 Digits: " + userSession.getSsnLastFour();
    }
}

@SessionScope
class UserSession {

    private String username;
    private String ssnLastFour;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getSsnLastFour() {
        return ssnLastFour;
    }

    public void setSsnLastFour(String ssnLastFour) {
        this.ssnLastFour = ssnLastFour;
    }
}