import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Passwd {
    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length != 1) {
            System.out.println("Usage: java Passwd <username>");
            return;
        }
        
        String username = args[0];
        String[] cmd = {"cat", "/etc/passwd"};
        
        ProcessBuilder processBuilder = new ProcessBuilder(cmd);
        Process process = processBuilder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while((line = reader.readLine()) != null) {
            if (line.startsWith(username + ":")) {
                System.out.println(line);
                break;
            }
        }
    }
}