import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Secret {

    public static void main(String[] args) throws IOException {
        File file = new File("secret.txt");
        FileWriter writer = new FileWriter(file);
        try {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } finally {
            writer.close();
        }
    }
}