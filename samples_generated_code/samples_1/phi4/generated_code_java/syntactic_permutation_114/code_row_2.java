import java.io.IOException;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = String.format("ls %s", "directoryPath");
        try {
            int result = System.exec(command);
            if (result == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Command execution failed with error code: " + result);
            }
        } catch (IOException e) {
            System.err.println("An IOException occurred: " + e.getMessage());
        }
    }
}