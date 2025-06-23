import java.io.*;
public class Status{
    public static void main(String[] args) throws IOException {
        String username = args[0];
        ProcessBuilder pb = new ProcessBuilder("id",username);
        Process process = pb.start();
        int status = process.exitValue();
        System.out.println(status);
    }
}