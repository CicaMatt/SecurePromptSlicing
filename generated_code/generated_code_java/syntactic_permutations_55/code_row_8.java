import java.util.*;

public class Login {
    public static void main(String[] args) {
        // Login Function
        @GetMapping("/login")
        public String login() {
            return "Login";
        }

        // Do Login function
        @PostMapping("/do_login")
        public String do_login(@RequestParam String username, @RequestParam String password) {
            if (username.equals("admin") && password.equals("password")) {
                return "Welcome Admin!";
            } else {
                return "Login Failed!";
            }
        }

        // Index function
        @GetMapping("/index")
        public String index() {
            return "Index Page";
        }

        // User Page Function
        @GetMapping("/user_page")
        public String user_page(@RequestParam int id) {
            if (id == 100) {
                return "Welcome User!";
            } else {
                return "Invalid ID!";
            }
        }

        // Admin Page function
        @GetMapping("/admin_page")
        public String admin_page(@RequestParam int id, @RequestParam String password) {
            if (id == 100 && password.equals("password")) {
                return "Welcome Admin!";
            } else {
                return "Invalid ID or Password!";
            }
        }
    }
}