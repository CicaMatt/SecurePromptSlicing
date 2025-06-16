package com.company;

import java.util.*;
public class Login {
    public static void login(String username, String password) {
        if (usernameExists(username)) {
            if (checkPassword(username, password)) {
                redirectToHomePage();
            } else {
                return;
            }
        }
    }

    private static boolean usernameExists(String username) {
        // Query database for matching username
        return true;
    }

    private static boolean checkPassword(String username, String password) {
        // Query database for matching password
        return true;
    }

    private static void redirectToHomePage() {
        // Redirect to home page
    }
}