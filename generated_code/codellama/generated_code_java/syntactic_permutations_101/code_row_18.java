import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("important_config");
        fw.write("important_config");
        fw.close();
    }
}