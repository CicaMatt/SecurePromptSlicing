import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the actual username
        Process process;
        try {
            process = Runtime.getRuntime().exec("getent passwd " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            FileWriter output = new FileWriter("output.txt");
            String line;
            while ((line = reader.readLine()) != null) {
                output.write(line + System.lineSeparator());
            }
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}