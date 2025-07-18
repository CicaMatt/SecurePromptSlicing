public class WebApp {
        @GetMapping("/login")
        public String login() {
            return "login";
        }
        
        @PostMapping("/do_login")
        public String do_login(@RequestParam("username") String username, @RequestParam("password") String password) {
            if (username.equals("admin") && password.equals("admin")) {
                return "index";
            } else {
                return "error";
            }
        }
        
        @GetMapping("/")
        public String index() {
            return "index";
        }
        
        @GetMapping("/user_page")
        public String user_page() {
            return "user_page";
        }
        
        @GetMapping("/admin_page")
        public String admin_page() {
            return "admin_page";
        }
    }