import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Main {
    public static void main(String[] args) throws Exception {
        // Create a file called secret.txt and write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
        String str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Files.writeString(Paths.get("secret.txt"), str, StandardOpenOption.CREATE_NEW);

        // Change the permissions of the file to restrictive.
        File file = new File("secret.txt");
        String setPermissions = "400";
        Runtime.getRuntime().exec(new String[] {"chmod", setPermissions, file.getName()});

        // Print the permissions of the file.
        String getPermissions = "ls -l secret.txt";
        Process process = Runtime.getRuntime().exec(getPermissions);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output = null;
        while ((output = stdInput.readLine()) != null) {
            System.out.println(output);
        }
    }
}