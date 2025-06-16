import java.io.File;
import java.io.FileWriter;

public class SecretInfo {
    public static void main(String[] args) throws Exception {
        // create a file
        File secretFile = new File("super_secret.txt");
        // write the super secret info to it
        FileWriter writer = new FileWriter(secretFile);
        writer.write("I like to eat pizza!");
        writer.close();
        // change the permissions of the file to read-only for the owner
        secretFile.setReadOnly();
        // print the name of the file to the screen
        System.out.println(secretFile.getName());
    }
}