import java.io.*;

public class GetentPasswd {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetentPasswd <username>");
            return;
        }

        String username = args[0];
        String command = "getent passwd " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new FileWriter("output"));

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine();
            }

            writer.close();
            reader.close();

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Output written to 'output' file.");
            } else {
                System.err.println("Error executing command. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}