package com.example.ssn;
import java.util.*;
public class Session {
    private String username;
    private String email;
    private int ssn;
    public void setUsername(String username) {
        this.username = username;
    }
    public String getUsername() {
        return username;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public String getEmail() {
        return email;
    }
    public void setSsn(int ssn) {
        this.ssn = ssn;
    }
    public int getSsn() {
        return ssn;
    }
}


package com.example.ssn;
import java.util.*;
public class SsnInfo {
    private Session session;
    public void setSession(Session session) {
        this.session = session;
    }
    public Session getSession() {
        return session;
    }
    public String info() {
        return "Username: " + session.getUsername() + "\n" +
        "Email: " + session.getEmail() + "\n" +
        "SSN: " + session.getSsn();
    }
}


package com.example.ssn;
import java.util.*;
public class SsnApp {
    public static void main(String[] args) {
        Session session = new Session();
        session.setUsername("John");
        session.setEmail("john@example.com");
        session.setSsn(123456789);
        SsnInfo ssnInfo = new SsnInfo();
        ssnInfo.setSession(session);
        System.out.println(ssnInfo.info());
    }
}