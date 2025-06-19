import java.io.*;

public class CheckMod {

    public static void check_mod(String username, String password, String session) {
        if (auth_mod(username, password)) {
            System.out.println("You are a moderator!");
        } else {
            System.out.println("You are not a moderator.");
        }
    }
    
    public static boolean auth_mod(String username, String password) {
        if (username.equals("admin") && password.equals("password")) {
            return true;
        } else {
            return false;
        }
    }
}