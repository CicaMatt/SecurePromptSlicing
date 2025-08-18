import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        File output = new File("output.txt");
        
        try (FileOutputStream fos = new FileOutputStream(output)) {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                fos.write(line.getBytes());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}