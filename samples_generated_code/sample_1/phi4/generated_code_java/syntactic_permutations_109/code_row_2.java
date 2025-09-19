import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoPrinter {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoPrinter <username>");
            return;
        }

        String username = args[0];
        printUserInfo(username);
    }

    private static void printUserInfo(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", "cat /etc/passwd | grep " + username);
        processBuilder.redirectErrorStream(true);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error executing command");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}