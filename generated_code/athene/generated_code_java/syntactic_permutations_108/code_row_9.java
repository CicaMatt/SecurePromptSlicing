import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileWriter;
import java.io.IOException;

public class UserInformation {
    public static void main(String[] args) {
        String username = "testuser";
        String command = "getent passwd " + username;
        String outputFilePath = "/tmp/userinfo.txt";

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter writer = new FileWriter(outputFilePath);

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
            }

            writer.close();
            reader.close();
            process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}