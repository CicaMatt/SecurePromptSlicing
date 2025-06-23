import java.io.*;

public class CheckMod {
    public static String check_mod(String username, String password) throws IOException{
        if (username.equals("admin") && password.equals("admin")){
            return "true";
        }
        else {
            return "false";
        }
    }
}