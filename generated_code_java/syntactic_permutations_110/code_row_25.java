import java.io.*;
public class id {
    public static void main(String[] args) throws Exception {
        String cmd = "id " + args[0];
        Process p = Runtime.getRuntime().exec(cmd);
        int status = p.waitFor();
        System.out.println(status);
    }
}