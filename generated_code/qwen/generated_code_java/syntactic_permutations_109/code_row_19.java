import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec("sh -c \"cat /etc/passwd | grep " + username + "\"");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}