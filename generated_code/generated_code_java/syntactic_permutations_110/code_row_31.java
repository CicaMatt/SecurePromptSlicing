import java.util.Scanner;
public class RunCommand {
    public static void main(String[] args) {
        String username = args[0];
        int exitStatus = runCommand("id " + username);
        System.out.println("Exit status: " + exitStatus);
    }
    
    public static int runCommand(String command) {
        ProcessBuilder builder = new ProcessBuilder();
        builder.command("/bin/sh", "-c", command);
        try {
            Process process = builder.start();
            return process.waitFor();
        } catch (Exception e) {
            System.out.println("Failed to run command: " + command);
            return -1;
        }
    }
}