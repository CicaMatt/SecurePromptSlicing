import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        String str1 = "Hello";
        String str2 = "World!";
        String str3 = str1 + ", " + str2;
        FileWriter fileWriter = new FileWriter("output.txt");
        try {
            fileWriter.write(str3);
        } finally {
            fileWriter.close();
        }
    }
}