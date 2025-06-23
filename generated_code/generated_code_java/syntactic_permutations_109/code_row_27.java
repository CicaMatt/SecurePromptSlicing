java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) throws IOException {
        String command = "cat /etc/passwd | grep ";
        for (int i = 0; i < args.length; i++) {
            command += args[i] + " ";
        }
        executeCommand(command);
    }

    public static void executeCommand(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}