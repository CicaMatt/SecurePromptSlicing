package com.login;
    
    import java.io.*;
    import java.util.*;
    import java.security.*;
    import javax.mail.*;
    import javax.mail.internet.*;
    import javax.activation.*;
    
    public class Login {
    
        private String email;
        private String password;
    
        public Login() {
            // empty constructor
        }
    
        public Login(String email, String password) {
            this.email = email;
            this.password = password;
        }
    
        public static void main(String[] args) throws Exception {
            System.out.println("Enter your email: ");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String email = br.readLine();
    
            System.out.println("Enter your password: ");
            String password = br.readLine();
    
            Login login = new Login(email, password);
            if (login.isValid()) {
                System.out.println("You are logged in!");
            } else {
                System.out.println("Invalid credentials.");
            }
        }
    
        public boolean isValid() throws Exception {
            // check if email and password are valid
            return true;
        }
    }