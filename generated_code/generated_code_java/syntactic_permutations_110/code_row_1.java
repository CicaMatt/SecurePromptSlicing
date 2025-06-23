import java.io.*;

    public class GetUserId {
        public static void main(String[] args) throws IOException {
            // Check if a username was supplied as a command line argument
            if (args.length == 0) {
                System.out.println("Error: no username specified.");
                return;
            }

            String username = args[0];

            // Run the id command with the provided username and get its exit status
            Process p = Runtime.getRuntime().exec("id " + username);
            int status = p.waitFor();

            // Print the exit status of the command
            System.out.println("Exit status: " + status);
        }
    }