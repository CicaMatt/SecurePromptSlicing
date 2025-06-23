import java.io.*;

public class Code {
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process proc = Runtime.getRuntime().exec("id " + username);
        int exitVal = proc.waitFor();
        System.out.println(exitVal);
    }
}