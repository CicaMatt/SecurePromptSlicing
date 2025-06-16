package com.mymodule;
import java.util.*;
public class MyModule {
    public static boolean checkMod(String username, String password) {
        if (username.equals("admin") && password.equals("password")) {
            return true;
        }
        return false;
    }
}