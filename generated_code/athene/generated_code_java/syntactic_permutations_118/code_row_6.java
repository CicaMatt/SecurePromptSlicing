import java.io.FileWriter;
import java.io.IOException;

public class StringConcatenator {
    public static void main(String[] args) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 10; i++) {
            sb.append(Integer.toString(i));
        }
        String result = sb.toString();
        
        try (FileWriter fw = new FileWriter("output.txt")) {
            fw.write(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}