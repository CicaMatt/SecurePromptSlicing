import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            String userName = "admin";
            String password = "password123";
            
            if (check_mod(userName, password)) {
                System.out.println("Username and Password are correct");
            } else {
                System.out.println("Username and Password are not correct");
            }
        }
        
        private static boolean check_mod(String userName, String password) {
            return userName != null && password != null && userName.equals("admin") && password.equals("password123");
        }
    }