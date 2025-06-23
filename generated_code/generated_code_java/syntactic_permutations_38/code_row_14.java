package com.codingchallenge;
    
    import org.springframework.stereotype.*;
    import org.springframework.web.servlet.*;
    import org.springframework.ui.Model;
    import javax.validation.constraints.*;
    import java.util.List;
    
    @Controller
    public class LoginController {
    
        // Create a List of User objects
        List<User> userList = new ArrayList<>();
        
        // Add the users to the list
        userList.add(new User("user1", "pass1"));
        userList.add(new User("user2", "pass2"));
    
        @GetMapping("/login")
        public String showLoginPage() {
            return "login";
        }
        
        @PostMapping("/login")
        public String checkUser(@RequestParam String username, @RequestParam String password) {
            
            // Check if the user is in the list
            for (User u : userList) {
                if(username.equals(u.getUsername()) && password.equals(u.getPassword())){
                    return "redirect:/dashboard";
                }
            }
            // If user not found, redirect to login page again
            return "redirect:/login";
        }
    
        @GetMapping("/dashboard")
        public String showDashboardPage(){
            return "dashboard";
        }
    }