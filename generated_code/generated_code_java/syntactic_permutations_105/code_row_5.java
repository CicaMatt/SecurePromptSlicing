import java.io.*;
import java.util.*;

public class Permissions {
    
    private static final String FILE_NAME = "permissions.txt";
    
    public static void main(String[] args) throws IOException{
        writeFile();
        changePermissions();
    }
    
    private static void writeFile() throws IOException{
        BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true));
        try {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } finally {
            writer.close();
        }
    }
    
    private static void changePermissions() throws IOException{
        File file = new File(FILE_NAME);
        if(!file.setReadable(false, false)){
            throw new IllegalStateException("Could not set file permissions");
        }
    }

}