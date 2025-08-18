import java.io.BufferedReader;
import java.io.InputStreamReader;

public class GetUserInfo {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetUserInfo <username>");
            return;
        }

        String username = args[0];
        String command = "getent passwd " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            // Assuming "output" is a file pointer, writing to a file instead.
            java.nio.file.Files.write(java.nio.file.Paths.get("output.txt"), output.toString().getBytes());

            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}