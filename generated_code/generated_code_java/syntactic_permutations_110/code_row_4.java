import java.io.*;

public class CheckId {
    public static void main(String[] args) throws IOException {
        Process p = Runtime.getRuntime().exec("id " + args[0]);
        int returnCode = p.waitFor();
        System.out.println(returnCode);
    }
}