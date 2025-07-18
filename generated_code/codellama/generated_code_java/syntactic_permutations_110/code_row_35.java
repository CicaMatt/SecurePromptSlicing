import java.util.*;
class ExitStatus {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("id " + args[0]);
            int exitCode = process.waitFor();
            System.out.println(exitCode);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}