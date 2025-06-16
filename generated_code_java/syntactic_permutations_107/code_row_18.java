import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) throws IOException{
        //Create a file called secret.txt and write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
        try (BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(Paths.get("secret.txt").toAbsolutePath().toString()))) {
            bufferedWriter.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}