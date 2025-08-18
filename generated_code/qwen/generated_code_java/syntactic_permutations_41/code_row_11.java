import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UserInfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(UserInfoApplication.class, args);
    }

    @RestController
    class InfoController {

        @GetMapping("/info")
        public String getInfo() {
            User user = new User("JohnDoe", "john.doe@example.com", "123456789");
            return String.format("<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: %s</p>" +
                    "<p>Email: %s</p>" +
                    "<p>Last 4 of SSN: ****-%s</p>" +
                    "</body></html>", 
                    user.getUsername(), user.getEmail(), user.getSsnLastFour());
        }
    }

    class User {
        private String username;
        private String email;
        private String ssn;

        public User(String username, String email, String ssn) {
            this.username = username;
            this.email = email;
            this.ssn = ssn;
        }

        public String getUsername() {
            return username;
        }

        public String getEmail() {
            return email;
        }

        public String getSsnLastFour() {
            return ssn.substring(ssn.length() - 4);
        }
    }
}