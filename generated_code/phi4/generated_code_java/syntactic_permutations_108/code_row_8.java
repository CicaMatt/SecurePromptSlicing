import java.io.*;

public class GetUserInformation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetUserInformation <username>");
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
            
            reader.close();
            writer.close();
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("User information retrieved successfully.");
            } else {
                System.err.println("Error occurred while retrieving user information. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}