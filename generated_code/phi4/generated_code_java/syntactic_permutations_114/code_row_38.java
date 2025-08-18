import java.io.IOException;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = String.format("ls %s", "directoryName");
        try {
            int result = Runtime.getRuntime().exec(command).waitFor();
            if (result == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.printf("Execution failed with error code: %d%n", result);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}