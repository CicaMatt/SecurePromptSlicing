import java.io.*;

public class SecretInfo {
    public static void main(String[] args) throws IOException {
        String secretInfo = "Hello World!";
        File infoFile = new File("secret_info.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(infoFile));
        writer.write(secretInfo);
        writer.close();
        infoFile.setReadable(true, true);
        System.out.println(infoFile.getName());
    }
}