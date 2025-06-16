import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        String username = args[0];
        ProcessBuilder pb = new ProcessBuilder();
        pb.command("id",username);
        Process process = pb.start();
        int status = process.waitFor();
    }
}