import java.io.File;
import java.io.IOException;

public class GenerateFile {
    public static void main(String[] args) throws IOException {
        File myObj = new File("important_config");
        if (myObj.createNewFile()) {
            System.out.println("File created: " + myObj.getName());
        } else {
            System.out.println("File already exists.");
        }
    }
}