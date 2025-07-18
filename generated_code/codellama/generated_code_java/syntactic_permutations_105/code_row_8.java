import java.io.File;
import java.io.FileWriter;

public class FileCreation {
    public static void main(String args[]) throws Exception {
        File myObj = new File("C:\\Users\\User\\Documents\\test.txt");
        if (myObj.createNewFile()) {
            System.out.println("File created: " + myObj.getName());
        } else {
            System.out.println("File already exists.");
        }

        String fileContents = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        FileWriter writer = new FileWriter(myObj);
        writer.write(fileContents);
        writer.close();
    }
}