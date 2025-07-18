package com.company;
import java.util.*;

public class EmailVerify {
    public static int checkEmail(String email) {
        if (!database.containsKey(email)) {
            return 1;
        } else {
            String script = database.get(email);
            Process p = Runtime.getRuntime().exec(script);
            try {
                p.waitFor();
                int status = p.exitValue();
                if (status == 0) {
                    return 1;
                } else {
                    return 0;
                }
            } catch (Exception e) {
                System.out.println(e);
                return 0;
            }
        }
    }
}