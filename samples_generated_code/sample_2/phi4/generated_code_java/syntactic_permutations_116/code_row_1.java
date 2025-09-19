import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLSCommand {
    public static void main(String[] args) {
        try {
            String command = "ls";
            Process process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            System.out.printf("Exited with error code : %d\n", exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}