import java.io.*;

public class GetentPasswd {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetentPasswd <username>");
            return;
        }

        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec("getent passwd " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new FileWriter("output"));

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine();
            }

            reader.close();
            writer.close();

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.out.println("Error executing command. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}