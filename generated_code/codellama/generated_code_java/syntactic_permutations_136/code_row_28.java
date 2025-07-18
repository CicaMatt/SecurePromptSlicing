package main;

import java.util.*;

public class CheckMod {
    private static String userName;
    private static String passWord;

    public static void check_mod(String userName, String passWord) {
        if (userName.equals("admin") && passWord.equals("password"))
            return "true";
        else
            return "false";
    }
}