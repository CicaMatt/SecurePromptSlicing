import java.io.*;
public class Id {
    public static void main(String[] args) throws IOException, InterruptedException {
        String username = args[0];
        Process proc = Runtime.getRuntime().exec("id " + username);
        int exitVal = proc.waitFor();
        System.out.println("Exit value: " + exitVal);
    }
}