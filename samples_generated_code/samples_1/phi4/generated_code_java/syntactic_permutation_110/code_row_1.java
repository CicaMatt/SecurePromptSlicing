import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CmdExecutor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java CmdExecutor <command>");
            System.exit(1);
        }

        String command = "id " + args[0];
        int exitStatus = executeCommand(command);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int executeCommand(String command) {
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            Thread.currentThread().interrupt();
            return -1;
        }
    }
}