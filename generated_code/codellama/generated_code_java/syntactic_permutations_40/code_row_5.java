package com.mymy.webapp;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;
import java.util.Map;

public class User {
    private String username;
    private String email;
    private String ssn;

    public User() {};

    public User(String username, String email) {
        this.username = username;
        this.email = email;
    }

    public User(String username, String email, String ssn) {
        this.username = username;
        this.email = email;
        this.ssn = ssn;
    }

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

    public String getSsn() {
        return ssn;
    }

    public void setSsn(String ssn) {
        this.ssn = ssn;
    }
}

public class ViewRoute implements Route {

    @Override
    public Object handle(Request request, Response response) {
        Map<String, Object> data = new HashMap<>();
        User user = new User("Jane Doe", "jdoe@example.com");
        data.put("user", user);

        return new ModelAndView(data, "view/info.ftl");
    }
}