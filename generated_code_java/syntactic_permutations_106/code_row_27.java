import java.io.*;
public class JavaWritePermissions {
    public static void main(String[] args) throws IOException {
        String superSecretInfo = "This is a very confidential information";
        File secretFile = new File("secretfile.txt");
        BufferedWriter bw = new BufferedWriter(new FileWriter(secretFile));
        bw.write(superSecretInfo);
        bw.close();
        if (secretFile.setReadable(true, true)) {
            System.out.println("Written to " + secretFile.getName());
            System.out.println("Changed permissions of " + secretFile.getPath() + " to read-only");
        }
    }
}