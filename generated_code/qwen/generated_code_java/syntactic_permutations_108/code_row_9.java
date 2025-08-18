import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        String username = "yourUsernameHere"; // Replace with the actual username
        ProcessBuilder processBuilder = new ProcessBuilder("getent", "passwd", username);
        
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter writer = new FileWriter("output");
            
            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.flush();
            }
            
            writer.close();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}