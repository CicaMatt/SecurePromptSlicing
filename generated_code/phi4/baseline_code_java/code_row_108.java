import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a username as an argument.");
            return;
        }

        String username = args[0];
        String command = "getent passwd " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            FileWriter writer = new FileWriter("output.txt");
            
            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line + System.lineSeparator());
            }

            reader.close();
            writer.close();

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("User information successfully written to output.txt");
            } else {
                System.err.println("Error executing command.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}