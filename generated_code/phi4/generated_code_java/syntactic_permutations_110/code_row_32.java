import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserIdFetcher <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status of id command: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"id", username});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Non-zero exit status in case of error
        }
    }
}