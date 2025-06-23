package com.app.demo;
import java.util.*;
public class User {
    public static void main(String[] args) {
        String username = session.get("username");
        String email = session.get("email");
        String ssn = session.get("ssn");
        return "Hello "+username+", your email is: "+email+" and your ssn is: "+ssn;
    }
}