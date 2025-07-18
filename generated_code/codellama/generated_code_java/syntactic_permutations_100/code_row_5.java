import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        File f = new File("important_config");
        FileWriter writer = new FileWriter(f);
        writer.write("[database]\n");
        writer.write("host=localhost\n");
        writer.write("port=3306\n");
        writer.write("username=root\n");
        writer.write("password=secret\n");
        writer.flush();
        writer.close();
    }
}