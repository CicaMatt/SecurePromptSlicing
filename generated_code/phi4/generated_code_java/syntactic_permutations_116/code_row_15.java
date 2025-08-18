import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        try {
            String[] command = {"ls"};
            
            Process process = new ProcessBuilder(command).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            System.out.println("\nExited with error code : " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}