import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpSession;
import org.springframework.stereotype.Component;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @Component
    public static class UserInfo {
        private String username = "JohnDoe";
        private String email = "john.doe@example.com";
        private String ssnLastFourDigits = "1234";

        public String getUsername() {
            return username;
        }

        public String getEmail() {
            return email;
        }

        public String getSsnLastFourDigits() {
            return ssnLastFourDigits;
        }
    }

    @RestController
    @RequestMapping("/info")
    public static class InfoController {

        private final HttpSession session;

        public InfoController(HttpSession session) {
            this.session = session;
        }

        @GetMapping
        public UserInfo info() {
            UserInfo userInfo = (UserInfo) session.getAttribute("userInfo");
            if (userInfo == null) {
                userInfo = new UserInfo();
                session.setAttribute("userInfo", userInfo);
            }
            return userInfo;
        }
    }
}
