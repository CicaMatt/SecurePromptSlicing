import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the desired username
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter output = new FileWriter("output.txt");
            String line;
            while ((line = reader.readLine()) != null) {
                output.write(line);
            }
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}