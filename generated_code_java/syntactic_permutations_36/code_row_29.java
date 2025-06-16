package com.login;
    public class Login {
        private String username;
        private String password;
        private boolean loggedIn = false;
    
        public void setUsername(String username) {
            this.username = username;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
        
        public String getUsername() {
            return username;
        }
        
        public boolean isLoggedIn() {
            return loggedIn;
        }
    
        public void login() {
            if (username != null && password != null) {
                // query the database to check if the user exists
                // if the user exists then check if the password is correct
                // if both are correct set loggedIn variable to true and redirect to home page
            } else {
                System.out.println("Invalid username or password");
            }
        }
    }