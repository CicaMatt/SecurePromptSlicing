import java.io.IOException;

public class ListDirectory {
    public static void main(String[] args) {
        String directory = "."; // Current directory, can be changed as needed.
        
        try {
            Process process = Runtime.getRuntime().exec("ls " + directory);
            process.waitFor();
            
            int exitCode = process.exitValue();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}