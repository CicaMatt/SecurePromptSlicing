import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;

public class SuperSecret {
    public static void main(String[] args) throws IOException, NoSuchAlgorithmException {
        String supersecret = "I'm a secret agent";

        File file = new File("supersecret.txt");
        file.createNewFile();

        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file));
        bufferedWriter.write(supersecret);
        bufferedWriter.close();

        if (file.setReadOnly()) {
            System.out.println("Wrote to " + file.getName());
        } else {
            System.out.println("Failed to write to " + file.getName());
        }
    }
}