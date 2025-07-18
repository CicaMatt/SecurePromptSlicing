import java.io.*;
public class Secret {
    public static void main(String[] args) throws IOException {
        String secret = "This is a super secret message.";
        File file = new File("secretfile.txt");
        BufferedWriter output = new BufferedWriter(new FileWriter(file));
        output.write(secret);
        output.close();
        // Change permissions to read-only for the owner
        file.setReadable(true, true);
        file.setWritable(false, false);
        System.out.println("File name: " + file.getName());
    }
}