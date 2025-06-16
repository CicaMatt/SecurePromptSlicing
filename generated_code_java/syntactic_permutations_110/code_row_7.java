import java.io.*;
public class ExitCode {
    public static int getExitCode(String username) {
        try {
            Process p = Runtime.getRuntime().exec("id " + username);
            p.waitFor();
            return p.exitValue();
        } catch (Exception e) {
            return -1;
        }
    }
}