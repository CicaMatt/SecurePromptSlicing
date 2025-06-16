import java.io.*;

public class Login {
    public static boolean check_mod(String uname, String pass)  throws IOException{
        if (uname=="admin" && pass =="password") {
            return true;
        } else {
            return false;
        }
    }
}