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
        public String userInfo() {
            User user = new User("JohnDoe", "johndoe@example.com", "123456789");
            return "Username: " + user.getUsername() +
                   "<br>Email: " + user.getEmail() +
                   "<br>Last 4 of SSN: " + user.getSsn().substring(5);
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

        public String getSsn() {
            return ssn;
        }
    }
}