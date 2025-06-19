import java.io.*;

public class ImportantFile {
    public static void main(String[] args) throws IOException {
        // open the file in read-write mode, creating it if it doesn't exist
        FileWriter fw = new FileWriter("important_config", true);
        
        // write to the file
        fw.write("important_config");
        
        // close the file
        fw.close();
    }
}