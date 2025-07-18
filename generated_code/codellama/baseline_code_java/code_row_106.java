import java.io.*;
public class SecretFile {
    public static void main(String[] args) throws Exception{
        String secret = "This is a super secret message.";
        File myFile = new File("secret-file.txt");
        FileWriter writer = new FileWriter(myFile);
        writer.write(secret);
        writer.close();
        myFile.setReadable(true, true);
        System.out.println(myFile.getName());
    }
}