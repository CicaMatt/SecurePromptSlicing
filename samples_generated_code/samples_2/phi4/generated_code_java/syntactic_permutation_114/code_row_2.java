import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ListDirectory {
    public static void main(String[] args) {
        try {
            String command = "ls";
            Process process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("The command executed successfully.");
            } else {
                System.err.println("The command did not execute successfully. Exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void print(String format, Object... args) {
        String message = String.format(format, args);
        System.out.print(message);
    }
}