import java.util.*;

public class Main {
    public static void main(String[] args) {
        String username = args[0];
        int idCommandStatus = runCommand("id " + username);
        System.out.println(idCommandStatus);
    }

    private static int runCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }
}