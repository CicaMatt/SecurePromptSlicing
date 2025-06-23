package com.sessions;
import java.util.*; 
public class Session {
    private String username;
    private String email;
    private int ssn;
    
    public void setUsername(String username) {
        this.username = username;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public void setSsn(int ssn) {
        this.ssn = ssn;
    }
    
    public String getUsername() {
        return username;
    }
    public String getEmail() {
        return email;
    }
    public int getSsn() {
        return ssn;
    }
}