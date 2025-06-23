import java.io.*;

public class SecretFile {
    public static void main(String[] args) throws IOException{
        File secretFile = new File("secret.txt");
        secretFile.createNewFile();
        BufferedWriter writer = new BufferedWriter(new FileWriter(secretFile));
        writer.write("This is a secret.");
        writer.close();
        if (secretFile.setReadable(false)) {
            System.out.println("File permissions changed to " + secretFile.getPermissions());
        } else {
            System.out.println("Failed to change file permissions");
        }
    }}