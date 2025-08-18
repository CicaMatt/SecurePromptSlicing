import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDInfo {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        String username = args[0];
        try {
            String commandOutput = executeCommand("id " + username);
            System.out.println(commandOutput);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String executeCommand(String command) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", command);
        Process process = processBuilder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        return output.toString().trim();
    }
}