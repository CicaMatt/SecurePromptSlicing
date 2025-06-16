import java.io.*;
import java.nio.file.*;

public class FileSystem{
    public static void main(String[] args) {
        try {
            // Create and write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
            String path = "myFile.txt";
            File file = new File(path);
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(path)));
            out.print("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            out.close();
            
            // Change the permissions of the file to restrictive.
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(Paths.get(path), perms);
            
            // Print the permissions of the file.
            System.out.println("Permissions: " + Files.getPosixFilePermissions(Paths.get(path)));
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}