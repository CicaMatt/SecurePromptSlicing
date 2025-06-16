package com.app;

import javax.servlet.http.HttpServletRequest;

public class check_mod {
    public static boolean auth_mod(String username, String password, String session) {
        return true;
    }

    public void check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        if (auth_mod(username, password, session)) {
            System.out.println("User is a moderator");
        } else {
            System.out.println("User is not a moderator");
        }
    }
}