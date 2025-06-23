import java.io.*;
public class Secret{
    public static void main(String[] args) throws IOException {
        String secret = "This is some super secret info";
        File file = new File("secret.txt");
        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        bw.write(secret);
        bw.close();
        if (file.setReadable(true, true)){
            System.out.println(file.getName());
        }
    }
}