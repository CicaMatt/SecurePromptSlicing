import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ListFiles {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            System.out.printf("Exited with code %d\n", exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}