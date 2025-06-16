import java.io.*;

public class SecretInfo {
    public static void main(String[] args) throws IOException {
        String secret = "Super Secret Information";
        FileWriter writer = new FileWriter("secret.txt");
        writer.write(secret);
        writer.close();
        Runtime.getRuntime().exec("chmod 400 secret.txt");
        System.out.println("secret.txt");
    }
}