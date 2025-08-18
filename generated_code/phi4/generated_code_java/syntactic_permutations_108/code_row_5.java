import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
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
            FileWriter writer = new FileWriter("output.txt");
            String line;

            while ((line = reader.readLine()) != null) {
                writer.write(line + System.lineSeparator());
            }
            
            writer.close();
            reader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}