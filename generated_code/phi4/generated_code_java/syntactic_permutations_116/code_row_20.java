import java.io.IOException;

public class ListFiles {
    public static void main(String[] args) {
        try {
            String command = "ls";
            Process process = Runtime.getRuntime().exec(command);
            
            int exitCode;
            do {
                exitCode = process.waitFor();
            } while (exitCode == 0);

            if (process.exitValue() != 0) {
                System.err.println("Error executing: " + command);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}