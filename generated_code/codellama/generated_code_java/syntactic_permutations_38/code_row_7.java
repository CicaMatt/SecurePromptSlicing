package com.login;
    import java.util.*;
    
    public class Login {
        private String username;
        private String password;
        
        private static List<String[]> users = new ArrayList<>();
        
        static {
            users.add(new String[]{"admin", "password"});
            users.add(new String[]{"user1", "password1"});
        }
    
        public void setUsername(String username) {
            this.username = username;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
        
        public boolean authenticate() {
            for (String[] user : users) {
                if (user[0].equals(username) && user[1].equals(password)) {
                    return true;
                }
            }
            
            return false;
        }
        
        public String getDashboard() {
            if (authenticate()) {
                return "Dashboard";
            } else {
                return "Login";
            }
        }
    }