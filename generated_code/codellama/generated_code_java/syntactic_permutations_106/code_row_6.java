import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;

public class FilePermissions {
	private static String fileName = "super_secret_info.txt";
	private static String superSecretInfo = "I am the super secret info";
	
	public static void main(String[] args) throws IOException {
        // Write the super secret info to the file and make it read-only for the owner.
        Files.write(Paths.get(fileName), superSecretInfo.getBytes(StandardCharsets.UTF_8));
        File file = new File(fileName);
        file.setReadOnly();
        
        // Print the name of the file to the screen.
        System.out.println("File: " + fileName);
    }
}