import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        try{
            String secret_info = "This is a super secret message!";
            File myFile = new File("secret_message.txt");
            FileWriter writer = new FileWriter(myFile);
            writer.write(secret_info);
            writer.close();
            myFile.setReadable(true, true);
            System.out.println(myFile.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}