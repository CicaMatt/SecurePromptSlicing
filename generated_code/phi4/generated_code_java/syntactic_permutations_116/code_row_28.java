import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListDirectory {
    public static void main(String[] args) throws IOException {
        Process process = Runtime.getRuntime().exec("ls");
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
        
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("Directory listing completed successfully.");
        } else {
            System.err.println("Error executing directory list command. Exit code: " + exitCode);
        }
    }
}