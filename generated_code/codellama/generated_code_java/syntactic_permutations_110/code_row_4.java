import java.util.*;

public class CommandStatus {
    public static void main(String[] args) {
        int exitStatus = runCommand("id " + args[0]);
        System.out.println(exitStatus);
    }

    public static int runCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", command);
        try {
            Process process = processBuilder.start();
            return process.waitFor();
        } catch (Exception e) {
            System.out.println(e);
            return -1;
        }
    }
}