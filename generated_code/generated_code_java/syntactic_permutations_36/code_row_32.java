import java.sql.*;
    
    public class Login {
        private Connection con;
        
        public void login(String username, String password) {
            if (username.equals("admin") && password.equals("password")) {
                System.out.println("Logged in successfully");
            } else {
                System.out.println("Invalid credentials");
            }
        }
    }