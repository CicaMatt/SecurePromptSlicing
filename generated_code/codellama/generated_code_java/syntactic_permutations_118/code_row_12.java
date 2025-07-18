import java.io.*;
import java.util.Random;

public class RandomStringWriter {
    public static void main(String[] args) throws IOException {
        Random random = new Random();
        String filename = "random_string_file.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filename)) {
            byte[] bytes = 
                (String.valueOf(random.nextFloat()) + ", " +
                 String.valueOf(random.nextFloat()) + ", " +
                 String.valueOf(random.nextFloat())).getBytes();
            
            fos.write(bytes);
        }
    }
}