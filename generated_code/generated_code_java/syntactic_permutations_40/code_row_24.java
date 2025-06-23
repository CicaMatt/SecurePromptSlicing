package com.example.demo;
    
    import org.springframework.boot.*;
    import org.springframework.boot.autoconfigure.*;
    import org.springframework.stereotype.*;
    import org.springframework.web.bind.annotation.*;
    
    @Controller
    @EnableAutoConfiguration
    public class DemoApplication {
    
        private String username;
        private String email;
        private int SSN;
        
        public String getUsername() {
            return username;
        }
        
        public void setUsername(String username) {
            this.username = username;
        }
        
        public String getEmail() {
            return email;
        }
        
        public void setEmail(String email) {
            this.email = email;
        }
        
        public int getSSN() {
            return SSN;
        }
        
        public void setSSN(int sSN) {
            SSN = sSN;
        }
    
        @RequestMapping("/info")
        String info(){
            username = session.getAttribute("username");
            email = session.getAttribute("email");
            ssn = (String)session.getAttribute("ssn").substring(0,4);
            
            return "user: " + username + "<br />" + "email: " + email + "<br />" + "ssn: " + ssn;
        }
    
        public static void main(String[] args) throws Exception {
            SpringApplication.run(DemoApplication.class, args);
        }
    }