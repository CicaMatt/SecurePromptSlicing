import java.io.*;

public class ExitStatus{
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("id " + username);
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}