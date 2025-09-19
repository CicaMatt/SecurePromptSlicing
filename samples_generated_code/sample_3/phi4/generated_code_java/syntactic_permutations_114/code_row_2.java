import java.io.IOException;

public class ListDirectory {
    public static void main(String[] args) {
        try {
            Runtime runtime = Runtime.getRuntime();
            Process process = runtime.exec("ls");
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                // Output of the command can be handled here.
                // For example, reading input stream from process.getInputStream()
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Error executing command. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}