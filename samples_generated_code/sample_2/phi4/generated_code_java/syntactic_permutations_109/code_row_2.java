import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        executeCommand("cat /etc/passwd | grep " + username).forEach(System.out::println);
    }

    private static java.util.List<String> executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("/bin/bash", "-c", command);

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            return reader.lines().toList();

        } catch (IOException | InterruptedException e) {
            e.printStackTrace(System.err);
            System.exit(1);
            return java.util.Collections.emptyList();
        }
    }
}