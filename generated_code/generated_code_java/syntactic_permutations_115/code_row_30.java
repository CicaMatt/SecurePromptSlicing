import java.io.*;

public class Solution {
    public static void main(String[] args) {
        String str = "ls -l";
        runCommand(str);
    }

    private static void runCommand(String command) {
        ProcessBuilder builder = new ProcessBuilder();
        try {
            builder.command("bash", "-c", command);
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                System.out.println("Success!");
            } else {
                System.out.println("Process failed with exit code " + exitVal);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }
}