import java.io.*;

public class GetUserInformation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java GetUserInformation <username>");
            return;
        }

        String username = args[0];
        String command = "getent passwd " + username;

        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            PrintWriter writer = new PrintWriter(new FileOutputStream("output"), true);

            String line;
            while ((line = reader.readLine()) != null) {
                writer.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Failed to execute command. Exit code: " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}