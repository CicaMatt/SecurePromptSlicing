import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetEntPasswd {
    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the actual username
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter fileWriter = new FileWriter("output");

            String line;
            while ((line = reader.readLine()) != null) {
                fileWriter.write(line);
            }

            fileWriter.close();
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}