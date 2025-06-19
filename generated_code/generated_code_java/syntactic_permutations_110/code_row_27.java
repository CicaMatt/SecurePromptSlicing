import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        Runtime rt = Runtime.getRuntime();
        String cmd = "id";
        Process pr = rt.exec(cmd + " " + args[0]);
        BufferedReader br = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        int exitStatus = pr.waitFor();
        System.out.println("Exit Status: " + exitStatus);
    }
}