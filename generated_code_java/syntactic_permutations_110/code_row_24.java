import java.util.*;
public class GetExitStatus {
    public static void main(String[] args) {
        String username = args[0];
        try {
            Process p = Runtime.getRuntime().exec("id " + username);
            int exitStatus = p.waitFor();
            System.out.println(exitStatus);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}