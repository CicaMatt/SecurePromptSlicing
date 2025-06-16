import java.io.*;
public class SecretInfo {
    public static void main(String[] args) throws Exception {
        // Create a string with some super secret info.
        String secret = "My secret is that I'm a pizza cutter!";
        
        // Create a file and write the super secret info to it.
        FileOutputStream outFile = new FileOutputStream("secretInfo.txt");
        DataOutputStream dataOut = new DataOutputStream(outFile);
        dataOut.writeUTF(secret);

        // Change the permissions of to read-only for the owner.
        String path = "secretInfo.txt";
        File f = new File(path);
        f.setReadable(true, true);

        // Print the name of to the screen.
        System.out.println("The secret info is in: " + path); 
    }
}