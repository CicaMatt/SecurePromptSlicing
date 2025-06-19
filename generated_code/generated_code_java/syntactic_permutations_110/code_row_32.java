import java.io.*;
public class ExitStatus {
    public static void main(String[] args) throws Exception {
        int i=0;
        ProcessBuilder pb = new ProcessBuilder("id",args[0]);
        Process process = pb.start();
        i=process.exitValue();
        System.out.println(i);
    }
}