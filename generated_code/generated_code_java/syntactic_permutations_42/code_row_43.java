package com.example.myapplication;
import static spark.Spark.*;
import org.apache.commons.lang3.StringUtils;
import java.util.*;
public class User {
    public String username = "";
    public String email = "";
    public long ssn = 0L;
}
public class info {
    public static User createUser() {
        User user = new User();
        user.username = "John";
        user.email = "john@example.com";
        user.ssn = 123456789L;
        return user;
    }
}
public class Main {
    public static void main(String[] args) {
        get("/info", (req, res) -> info.createUser());
    }
}